#include <stdio.h>
#include <math.h>
#include <string.h>
#include "info.h"
#include "books.h"
#include "sections.h"

/******************** PR2 - EX3A ********************/
tError si_getSectionInfo(tBookTable tabB, tSectionTable tabS, char sectionId, tSectionInfo *si ){
	tError retVal = OK;
	unsigned int i;
	unsigned int j;
	unsigned int k;
	unsigned int sectionFound = 0;

	#ifdef SIMPLE_VERSION
	
	//Initialize subsections
	for(i=0;i<MAX_SUB;i++) {
		si->secSubs[i].id = 0;
		si->secSubs[i].subBooks[i]=0;
		si->secSubs[i].totSubBooks = 0;
		
		si->secSubs[i].subBooks[i] = 0;
	}
	si->totSecBooks = 0;
	si->totSecSubs = 0;
	
	//Loop all sections
	for(i=0;i<tabS.size;i++) {
		//If section exist in the table of sections
		if(tabS.table[i].id==sectionId) {
			sectionFound++;
			strcpy(&si->section.id,&tabS.table[i].id);
			strcpy(si->section.name,tabS.table[i].name);
			
			//Loop all books in the books table
			for(j=0;j<tabB.size;j++) {
				//If section exist in the books table
				if(tabB.table[j].clas.secId==sectionId) {
					//Loop all subsections until max. subsections of 10
					for(k=0;k<tabB.size;k++) {
						//If position in the vector is empty then add subsection
						if(si->secSubs[k].id == 0){
							strcpy(&si->secSubs[k].id,&tabB.table[j].clas.subId);
							si->secSubs[k].subBooks[si->secSubs[k].totSubBooks] = bookTable_find(tabB,tabB.table[j].ISBN);
							si->totSecSubs++; //One more subsection in the section
							si->secSubs[k].totSubBooks++; //One more book in the subsection
							break;
						//If the subsection already exist
						}else if (si->secSubs[k].id == tabB.table[j].clas.subId){
							si->secSubs[k].subBooks[si->secSubs[k].totSubBooks] = bookTable_find(tabB,tabB.table[j].ISBN);
							si->secSubs[k].totSubBooks++; //One more book in the subsection
							break;
						}
						if (k == MAX_SUB) break; //If max. subsections is reached end loop
					}
					si->totSecBooks++; //One more book in the section
				}		
			}
		} 
	}
	//No books in this section
	if (si->totSecBooks == 0) retVal = ERR_ENTRY_NOT_FOUND;
	
	//Section doesn't exist in sections table
	if (sectionFound == 0) retVal = ERR_INVALID_DATA;
				
	#endif
	#ifdef COMPLETE_VERSION	
/******************** PR2 - EX6A ********************/
	#endif 			

	return retVal;
}

/******************** PR2 - EX3B ********************/
tBook si_getBook(tBookTable tabB, tSectionInfo si, unsigned int nSub, unsigned int nBook) {
	tBook book;
	
	#ifdef SIMPLE_VERSION

	book = tabB.table[si.secSubs[nSub].subBooks[nBook]];
		
	#endif
	#ifdef COMPLETE_VERSION
/******************** PR2 - EX6A ********************/
	#endif	

	return book;
}

/******************** PR2 - EX3C ********************/
void si_listSectionInfo(tBookTable tabB, tSectionInfo si){
	unsigned int i;
	unsigned int j;
	tBook book;
	char str[MAX_LINE];
	
	#ifdef SIMPLE_VERSION
	
	getSectionStr(si.section, MAX_LINE, str);
	printf("\nSection %s: %d subsections, %d books", str,si.totSecSubs,si.totSecBooks);
	for(i=0;i<si.totSecSubs;i++) {
		printf("\nSubsection %c: %d books:",si.secSubs[i].id,si.secSubs[i].totSubBooks);
		for(j=0;j<si.secSubs[i].totSubBooks;j++) {
			book = si_getBook(tabB,si,i,j);
			getBookStr(book, MAX_LINE, str);
			printf("\n%s",str);
		}
	}
	
	printf("\n");
	#endif
	#ifdef COMPLETE_VERSION	
/******************** PR2 - EX6A ********************/
	#endif 			
	
}