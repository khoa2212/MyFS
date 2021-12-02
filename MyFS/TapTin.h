#pragma once

#include "entry.h"

class File : public Entry
{
public:
	File() = default;
	File(Entry const& entry);
	~File();

	void display(bool selected) override;

	Entry* add(Entry const& entry) override;
	void del(Entry* entry) override;
	vector<Entry*> getSubEntryList() const override;
	bool hasChildWithTheSameName(Entry const& entry) const override;
};

