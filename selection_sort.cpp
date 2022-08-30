#include <utility>
#include <omp.h>


template<typename RandomAccessIterator, typename Comparator>
double selection_sort(RandomAccessIterator first, RandomAccessIterator last, Comparator comp) {
	double start_time = omp_get_wtime();

	RandomAccessIterator start = first;
	while (start != last) {
		RandomAccessIterator swapped_next_global = start;
		#pragma omp parallel
		{
			// Find the next element to be moved
			RandomAccessIterator swapped_next = start;
			#pragma omp for
			for (RandomAccessIterator i = start+1; i != last; i++) {
				if (comp(*i, *swapped_next)) {
					swapped_next = i;
				}
			}

			#pragma omp critical
			{
				if (comp(*swapped_next, *swapped_next_global)) {
					swapped_next_global = swapped_next;
				}
			}
			#pragma omp barrier

			#pragma omp single
			{
				// Move the element to the correct spot
				std::swap(*start, *swapped_next_global);
				start++;
				swapped_next_global = start;
			}
		}
	}

	double end_time = omp_get_wtime();
	return end_time - start_time;
}
