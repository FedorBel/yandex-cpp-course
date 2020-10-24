#include "ini.h"

namespace Ini
{
	pair<string_view, string_view> Split(string_view line, char by) {
		size_t pos = line.find(by);
		string_view left = line.substr(0, pos);

		if (pos < line.size() && pos + 1 < line.size()) {
			return { left, line.substr(pos + 1) };
		}
		else {
			return { left, string_view() };
		}
	}
	string_view Unquote(string_view value) {
		if (!value.empty() && value.front() == '[') {
			value.remove_prefix(1);
		}
		if (!value.empty() && value.back() == ']') {
			value.remove_suffix(1);
		}
		return value;
	}
	Section & Document::AddSection(string name)
	{
		return sections[move(name)];
	}
	const Section & Document::GetSection(const string & name) const
	{
		return sections.at(name);
	}
	size_t Document::SectionCount() const
	{
		return sections.size();
	}
	Document Load(istream & input)
	{
		Document doc;
		Section* section = nullptr;
		for (string line; getline(input, line); ) {
			if (line.empty())
			{
				continue;
			}
			if (line[0] == '[') // create new section
			{
				section = &doc.AddSection(string(Unquote(line)));
				continue;
			}			
			// fill section
			auto[name, value] = Split(line, '=');
			if (section != nullptr)
				section->insert({ string(name), string(value) });
		}
		return doc;
	}
}
