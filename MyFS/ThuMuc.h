#include "entry.h"
#include "TapTin.h"

class Folder : public Entry
{
public:
	Folder() = default;
	Folder(Entry const& entry);
	~Folder();

	Entry* add(Entry const& tempEntry) override;
	void del(Entry* entry) override;
	vector<Entry*> getSubEntryList() const override;
	bool hasChildWithTheSameName(Entry const& entry) const override;

	void display(bool selected);
	void displayParent(bool selected);
	void show(int selected);
	int getListSize();
	Entry* getEntryInList(int i);

private:
	vector<Entry*> EntryList;
};

