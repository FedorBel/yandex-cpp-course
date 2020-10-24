template <typename RandomIt>
pair<RandomIt, RandomIt> FindStartsWith(
	RandomIt range_begin, RandomIt range_end,
	const string& prefix)
{
	string prefix_up = prefix;
	prefix_up.back() = ++prefix_up.back();
	
	auto lb = lower_bound(range_begin, range_end, prefix);
	auto ub = lower_bound(range_begin, range_end, prefix_up);

	return { lb,ub };
}