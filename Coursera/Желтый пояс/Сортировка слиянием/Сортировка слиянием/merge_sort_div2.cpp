template <typename RandomIt>
void MergeSort(RandomIt range_begin, RandomIt range_end)
{
	if ((range_end - range_begin) < 2)
	{
		return;
	}

	vector<typename RandomIt::value_type> elements(range_begin, range_end);	

	auto begin = elements.begin();
	auto border = elements.end() - elements.size() / 2;
	auto end = elements.end();	
	MergeSort(begin, border);
	MergeSort(border, end);
	merge(begin, border, border, end, range_begin);
}