/*
 ID 03138224, Li W. and ID 08569541, Chiu P.
 159.234 Assignment 2 Part 1
 Program to record Massey University Library items, using inheritance and polymorphism
 Included penalty cost for each item in printout
 */

#include <iostream>
#include <string>
#include <iomanip>
#include <sstream>

using namespace std;

const static string S_PROCESSED = "PROCESSEDtest02";
const static string S_ON_LOAN = "ON_LOAN";
const static string S_AVAILABLE = "AVAILABLE";
const static string S_OVERDUE = "OVERDUE";
const static string S_MISSING = "MISSING";

//-----------------------------------------------------------------------------
/**
 *Class listing for base class 'Item'
 */
class Item {
public:
	//constructor
	Item(string callNumber = "123.4567xyz", string type = "Book", string title =
			"My Book", string status = S_PROCESSED, string location =
			"Auckland -- main collection", int daysOverdue = 0) :
			mCallNumber(callNumber), mType(type), mTitle(title), mStatus(
					status), mLocation(location), mDaysOverdue(daysOverdue) {
	}
	//virtual destructor is to ensure the correct destructor is called
	virtual ~Item() {
	}

	void setCallNumber(const string callNumber) {
		mCallNumber = callNumber;
	}

	string getCallNumber() {
		return mCallNumber;
	}

	void setOverdue(const int readDaysOverdue) {
		mDaysOverdue = readDaysOverdue;
		mStatus = S_OVERDUE;
	}

	int getDaysOverdue() const {
		return mDaysOverdue;
	}
	/**
	 *virtual function print(): prints all details for the item object
	 */
	virtual void print() const {
		cout << left << //
				setw(10) << mType << //
				setw(20) << mCallNumber << //
				setw(65) << mTitle << //
				setw(40) << mLocation; //
		if (mDaysOverdue > 0) {
			stringstream sstream;
			string status;
			sstream << mStatus << " for " << mDaysOverdue
					<< " days, penalty is: $" << getFees();
			status = sstream.str();
			cout << setw(40) << status;
		} else {
			cout << setw(40) << mStatus;
		}

		//cout<<"Overdue for "<<mDaysOverdue<<" days;"<<" Penalty is: $"<<getFees() <<";";

	}
	//pure virtual function getFees(): for computing fees for overdue items
	virtual float getFees() const = 0;

private:
	string mCallNumber;
protected:
	string mType;
	string mTitle;
	string mStatus;
	string mLocation;
	int mDaysOverdue;

};
//-----------------------------------------------------------------------------
/*
 Class listing for derived class 'Book' from base class 'Item'
 */
class Book: public Item {
public:
	Book(string callNumber = "111.2222aaa", string type = "Book", string title =
			"My Book", string status = S_PROCESSED, string location =
			"Auckland -- main collection", int daysOverdue = 0, string authors =
			"Jason", int numPages = 100) :
			Item(callNumber, type, title, status, location, daysOverdue), mAuthors(
					authors), mNumPages(numPages) {
	}
	~Book() {
	}
	virtual void print() const override;
	virtual float getFees() const {
		return (0.30 * mDaysOverdue);
	}
protected:
	string mAuthors;
	int mNumPages;
};

void Book::print() const {
	Item::print();
	cout << left << //
			setw(30) << mAuthors << //
			setw(5) << mNumPages << //
			endl;
}
//-----------------------------------------------------------------------------
/*
 Class listing for derived class 'Journal' from base class 'Item'
 */
class Journal: public Item {
public:
	Journal(string callNumber = "111.2222aaa", string type = "Book",
			string title = "My Book", string status = S_PROCESSED,
			string location = "Auckland -- main collection",
			int daysOverdue = 0, int frequency = 6, string publisher = "CNN") :
			Item(callNumber, type, title, status, location, daysOverdue), mFrequency(
					frequency), mPublisher(publisher) {
	}
	~Journal() {
	}
	virtual void print() const override;
	virtual float getFees() const {
		return (0.50 * mDaysOverdue);
	}
protected:
	int mFrequency;
	string mPublisher;
};

void Journal::print() const {
	stringstream freq;
	freq << mFrequency << " issues per year";
	string str = freq.str();

	Item::print();
	if (mFrequency > 0) {
		cout << left << setw(40) << str;
	} else {
		cout << left << setw(40) << "Info not available -online journal";
	}
	cout << setw(20) << mPublisher << //
			endl;
	/*
	 if (mFrequency>0){cout<<"Frequency: "<<mFrequency<<" issues per year ";}
	 else{cout<<"Info not available -online journal";}
	 cout<<" Published by: "<<mPublisher<<endl;
	 */
}

//-----------------------------------------------------------------------------
/*
 Class listing for derived class 'AV' from base class 'Item'
 */
class AV: public Item {
public:
	AV(string callNumber = "111.2222aaa", string type = "Book", string title =
			"My Book", string status = S_PROCESSED, string location =
			"Auckland -- main collection", int daysOverdue = 0, string subject =
			"Science") :
			Item(callNumber, type, title, status, location, daysOverdue), mSubject(
					subject) {
	}
	~AV() {
	}
	virtual void print() const override;
	virtual float getFees() const {
		return (1.5 * mDaysOverdue);
	}
protected:
	string mSubject;
};

void AV::print() const {
	Item::print();
	cout << left << //
			setw(20) << mSubject << //
			endl;
}
//-----------------------------------------------------------------------------
/*Displays information of the program's title and authors*/
void info();

//-----------------------------------------------------------------------------

/*Main function*/

int main() {
	info();
	Item *ptr[10];
	//Item(callNumber,type,title,status,location,daysOverdue),mAuthors(authors),mNumPages(numPages)
	ptr[0] = new Book("E-BOOK", "Book",
			"C++ how to program: introducing the new C++ 14 standard",
			S_AVAILABLE, "E-BOOK", 0, "Paul Deitel, Harvey Deitel", 1080);
	ptr[1] = new Book("005.133 C Sav", "Book", "Absolute C++", S_AVAILABLE,
			"Albany Main Collection (Level 5)", 0, "Walter Savitch", 975);
	ptr[2] = new Book("005.133C++ Gad", "Book",
			"Starting out with C++:from control structures through objects",
			S_OVERDUE, "Manawatu Main Collection (Level 2)", 6, "Tony Gaddis",
			1238);
	//Item(callNumber,type,title,status,location,daysOverdue),mFrequency(frequency),mPublisher(publisher)
	ptr[3] = new Journal("INTERNET", "Journal", "Communications of the ACM",
			S_AVAILABLE, "INTERNET", 0, 12, "ACM");
	ptr[4] = new Journal("INTERNET", "Journal", "Informal: Informatics Journal",
			S_AVAILABLE, "INTERNET", 0, 0, "Universitas Jember Indonesia");
	ptr[5] = new Journal("INTERNET", "Journal", "IEEE Transactions on Big Data",
			S_AVAILABLE, "INTERNET", 0, 4, "IEEE");
	//Item(callNumber,type,title,status,location,daysOverdue),mSubject(subject)
	ptr[6] = new AV("782.4208999442 Tri", "AV", "Music is Choice", S_OVERDUE,
			"Wellington Music DVD", 5, "music-rock");
	ptr[7] = new AV("782.42166 Gin", "AV", "Holy Smoke", S_AVAILABLE,
			"Manawatu NZ Collection (Level 2) DVD", 0, "music-jazz");
	ptr[8] = new AV("006.686 ADO E v. 5", "AV", "Video Lectures-Tony Hallas",
			S_OVERDUE, "Manawatu Main Collection (Level 2) DVD", 10,
			"movie-documentar");
	ptr[9] = new AV("791.4372 Ind", "AV", "The Adventures of Indiana Jones",
			S_MISSING, "Albany Feature Films (Level 1) DVD", 0,
			"movie-adventure");

	cout << "Printing all book items ...\n\n";
	cout << left << setw(10) << "TYPE:" << //
			left << setw(20) << "CALL NUMBER: " << //
			left << setw(65) << "TITLE: " << //
			left << setw(40) << "LOCATION: " << //
			left << setw(40) << "STATUS: " << //
			left << setw(30) << "AUTHORS:" << //
			left << setw(5) << "NUMBER OF PAGES:" << //

			endl;
	for (int i = 0; i < 3; ++i) {
		ptr[i]->print();
	}
	cout << endl;

	cout << "Printing all journal items ...\n\n";
	cout << left << setw(10) << "TYPE:" << //
			left << setw(20) << "CALL NUMBER: " << //
			left << setw(65) << "TITLE: " << //
			left << setw(40) << "LOCATION: " << //
			left << setw(40) << "STATUS: " << //
			left << setw(40) << "FREQUENCY: " << //
			left << setw(20) << "PUBLISHER:" << //

			endl;
	for (int i = 3; i < 6; ++i) {
		ptr[i]->print();
	}

	cout << endl;

	cout << "Printing all AV items ...\n\n";
	cout << left << setw(10) << "TYPE:" << //
			left << setw(20) << "CALL NUMBER: " << //
			left << setw(65) << "TITLE: " << //
			left << setw(40) << "LOCATION: " << //
			left << setw(40) << "STATUS: " << //
			left << setw(20) << "SUBJECT: " << //

			endl;
	for (int i = 6; i < 10; ++i) {
		ptr[i]->print();
	}

	cout << endl;
	//compute and print the total amount for all overdue items
	cout << "Total overdue amount so far is: $";
	float totalOverdue = 0;
	for (int i = 0; i < 10; ++i) {
		ptr[i]->getFees();
		totalOverdue += ptr[i]->getFees();
	}
	cout << totalOverdue << endl;

	//change the id of one item
	ptr[1]->setCallNumber("123.707 ADR");

	//print the modified item
	cout << "\nPrinting again..\n";
	ptr[1]->print();

	cout << "\n All done! Ciao!\n";
}
//-----------------------------------------------------------------------------
void info() {
	cout << "*******************************************" << endl;
	cout << "* 159.234 Assignment 2 part 1             *" << endl;
	cout << "* 03138224 Wei Li and 08569541 Peter Chiu *" << endl;
	cout << "*******************************************" << endl;
	cout << endl;
}
//-----------------------------------------------------------------------------

