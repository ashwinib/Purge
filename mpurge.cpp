
//--BEGIN Program--(st.cpp)------------------------------------------------
//
//	Description:	Purges a file of character strings of duplicate entries.
//					
//	Usage:			purge <input file> <optional output file>
//					If no output file is specified, the input file is overwritten.
//
//	Version	Date			Author		Comment
//	-------	----			------		-------
//	v1.0	20 Feb 1999		EECE352		Initial version
//	v1.1	18 Mar 1999		EECE352		Changed display to handle 7 digits
//	v1.2	10 Nov 2008		Unitrends	Modified for compilation on Windows and Linux
//


#include <iostream>
#include <fstream>
#include <iomanip>
#include <cstdlib>
#include <ctime>
#include <string>
#include "btree.h"
using namespace std;

class ListNode
	{
	public:
		string entry;
		ListNode *link;
	};

	void init(int, char *[ ]);
	void insert(string);
	void QueueEntry(string entry);

	int count = 0, duplicates = 0, entries = 0, NumQueued = 0, unique = 0;
	//TreeNode *root = NULL;
	ListNode *head = NULL;
	ListNode *sentinel = NULL;
	fstream fin, fout;
	bool OverWrite;

//--BEGIN FUNCTION--(main)----------------------------------------------

	int  main(int argc, char *argv[ ])
		{
		float CPU_time, StartTime;
		string buffer;
		ListNode *p;

		extern int unique;

		//cout << "  Purge Program v1.1" << endl;
		init(argc, argv);
		StartTime = (float) clock( );

		/*if(OverWrite)
			cout << "  Processing input file ...        " << flush;
		else
			cout << "  Creating output file ...        " << flush;*/
		while(!fin.eof( ))
			{
			fin >> buffer;
			if(fin.good( ))
				{
				entries++;
				insert(buffer);
				}
			//if(entries % 1000 == 0)
			//	cout << "\b\b\b\b\b\b\b" << setw(7) << entries << flush;
			}
		//cout << "\b\b\b\b\b\b\b" << setw(7) << entries << endl;
		if(OverWrite)
			if(duplicates == 0)
				cout << "  File did not contain duplicates and was not overwritten" << endl;
			else
				{
				fin.close( );
				fout.open(argv[1], ios::out);
				if(!fout)
					{
					cout << "  Can not open [" << argv[1] << "] as the output file" << endl;
					exit(1);
					}
				cout << "  Writing unique entries back to source file ...  " << endl;
				p = head;
				while(p != sentinel)
					{
					fout << p->entry << endl;
					p = p->link;
					}
				}
		cout << "  [" << entries << "] entries in file, [" << duplicates << "] duplicates, [" << unique << "] unique entries" << endl;
		CPU_time = (float) clock( ) - StartTime;
		if(CPU_time < 1000.0)
			cout << "  CPU time: [" << CPU_time << "] milliseconds" << endl;
		else
			cout << "  CPU time: [" << CPU_time/1000.0 << "] seconds" << endl;

		return 0;
		}

//--END FUNCTION--(main)-------------------------------------------------


//--BEGIN FUNCTION--(init)-------------------------------------------------

	void init(int argc, char *argv[ ])
		{
		if(argc < 2)
			{
			cout << "  purge <input file> <optional output file>" << endl;
			cout << "  If no output file is specified, the input file will be overwritten" << endl;
			exit(1);
			}
		fin.open(argv[1], ios::in);
		if(!fin)
			{
			cout << "  EXIT: Could not open [" << argv[1] << "] as input file" << endl;
			exit(1);
			}
		if(argc == 2)
			{
			OverWrite = true;
			head = NULL;
			sentinel = head;
			}
		else
			{
			fout.open(argv[2], ios::out);
			if(!fout)
				{
				cout << "  EXIT: Could not open ["  << argv[2] << "] as output file" << endl;
				exit(1);
				}
			OverWrite = false;
			}
		initRB();
		}

//--END FUNCTION--(init)----------------------------------------------------


//--BEGIN FUNCTION--(insert)---------------------------------------------

	 void insert(string entry)
		{
		TreeNode *p,*p2;
		extern int unique;
		p = new TreeNode;
		if(!p)
				{
				cout << "\tPROGRAM EXIT:  memory allocation error (insert)" << endl;
				exit(1);
				}
		p->entry = entry;
		p2 = insertinRB(p);
		if(p2 == p){
			unique++;
			//cout<<"\nInserting :"<<entry;
			if(OverWrite)
				QueueEntry(entry);
			else
				fout << entry << endl;
		}
		else{
			duplicates++;
			delete p;
		}

		//return p;
		}

//--END FUNCTION--(insert)------------------------------------------------


//--START FUNCTION--(QueueEntry)------------------------------------------


void QueueEntry(string entry)
	{
	ListNode	*p;

	p = new ListNode;
	if(!p)
		{
		cout << "PROGRAM HALTED: memory allocation error" << endl;
		exit(1);
		}

	if(NumQueued == 0)
		head = p;
	else
		sentinel->link = p;
	//
	//	Attach the new element to the end of the list:
	//
	sentinel = p;
	p->link = NULL;
	//
	//	Allocate space for the character string:
	//

	p->entry = entry;
	NumQueued++;
	}

//--END FUNCTION--(QueueEntry)--------------------------------------------



//--END PROGRAM--(SearchTree)----------------------------------------
