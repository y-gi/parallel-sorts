#include <utility>
#include <omp.h>


template<typename RandomAccessIterator, typename Comparator>
double insertion_sort(RandomAccessIterator first, RandomAccessIterator last, Comparator comp) {
	double start_time = omp_get_wtime();

	RandomAccessIterator unsorted = (first != last) ? first+1 : last;
	while (unsorted != last) {
		RandomAccessIterator inserted_next_global = unsorted;
		#pragma omp parallel
		{
			// Find the next element to be inserted into the sorted section
			RandomAccessIterator inserted_next = unsorted;
			#pragma omp for
			for (RandomAccessIterator i = unsorted+1; i != last; i++) {
				if (comp(*i, *inserted_next)) {
					inserted_next = i;
				}
			}

			#pragma omp critical
			{
				if (comp(*inserted_next, *inserted_next_global)) {
					inserted_next_global = inserted_next;
				}
			}
			#pragma omp barrier

			#pragma omp single
			{
				// Find the correct place to insert the element in the sorted section
				RandomAccessIterator insert_here = first;
				while (comp(*insert_here, *inserted_next)) {
					insert_here++;
				}
				// Insert the element
				for (RandomAccessIterator i = insert_here; i != unsorted; i++) {
					std::swap(*i, *inserted_next);
				}
				std::swap(*unsorted, *inserted_next);

				unsorted++;
			}
		}
	}

	double end_time = omp_get_wtime();
	return end_time - start_time;
}
