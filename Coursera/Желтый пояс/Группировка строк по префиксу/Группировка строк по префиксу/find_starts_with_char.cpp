template <typename RandomIt>
pair<RandomIt, RandomIt> FindStartsWith(RandomIt range_begin, RandomIt range_end, char prefix)
{
	string low_val;
	low_val = prefix;
	auto lb = std::partition_point(range_begin, range_end,
		[prefix](const auto& s) { return s.front() < prefix; });

	auto ub = std::partition_point(range_begin, range_end,
		[prefix](const auto& s) { return s.front() <= prefix; });

	return { lb,ub };
}