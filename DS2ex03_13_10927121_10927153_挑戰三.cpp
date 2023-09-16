/////////////10927121_�i���l_10927153_�d�W��
#include <iostream>           // cout, endl
#include <fstream>            // open, is_open, close, ignore
#include <string>             // string, find_last_of, substr
#include <vector>             // vector, push_back
#include <cstdlib>            // system, atoi
#include <iomanip>            // setw
#include <cmath>
#include <time.h>
#include <stdlib.h>
#include <string.h>

using namespace std;
using std::string ;

struct DATA {
			char sid[10] = {'\0'} ; // �Ǹ��A�n�O�o��l��
			char sname[10] = {'\0'} ; // �m�W�A�n�O�o��l��
			unsigned char one ; //����
			unsigned char two ;
			unsigned char three ;
			unsigned char four ;
			unsigned char five ;
			unsigned char six ;
			char temp ;
			float average ; // ��������
			int hvalue = 0 ;
};

class Probe {


	public:
		vector <DATA> step ;
		vector <DATA> garbage ;
		DATA data ;

		bool Is_num ( int &num ) {                                             // command���b (�ư��Ʀr�H�~����J)
   			string numstr ;
   			cin >> numstr ;
			if ( numstr == "0" ) {                                             // ��J������0
				num = 0 ;
	 			return true ;
 			} // if

			num = atoi( numstr.c_str() ) ;
  			if ( num == 0 ) return false ;
  			else return true ;
		} // Is_num()

		bool dataget ( string &filenum ) {
			string filename ;
			string before ;
			string str1 ;
			ifstream file ;
			step.clear() ; // �C�����Nstep��l��
			garbage.clear() ;
			bool success = false ;
			char str[500] ;


			while ( !success ) { // �O�_���\Ū���ɮ�


			  cout << endl << "Input a file number ([0] Quit):" ;
		   	  cin >> filenum ;
		   	  if ( filenum == "0" ) return false ;
		   	  filename = "input" + filenum + ".bin" ;
			  file.open( filename.c_str(), ios::binary ) ;
			  if ( !file ) {
			  	Mission0( filenum, success ) ;
			  } // if
			  else {
			    success = true ; //��bin�ɡA����Ū��
			    file.close() ;
			  } // else

			} // while

			//read bin
			file.open( filename.c_str(), ios::binary ) ;

			while ( file.read( data.sid, sizeof(data.sid) ) ) {

			  file.read( data.sname, sizeof(data.sname) ) ;
			  data.one = file.get()  ;
			  data.two = file.get() ;
			  data.three = file.get() ;
			  data.four = file.get() ;
			  data.five = file.get() ;
			  data.six = file.get() ;
			  data.temp = file.get() ;
			  data.temp = file.get() ;
			  file.read( (char*)&data.average, sizeof(data.average) ) ;
			  data.average = (float) data.average ;
			  step.push_back(data) ;

			} // while()

			file.close() ;
			return true ;
		} // dataget()

		void Mission0( string filenum, bool & success ) { // Ūtxt�ɡA��bin��
			fstream file ;
			string filename ;
			int num ;
			filename = "input" + filenum + ".txt" ;
			file.open( filename.c_str(), ios::in ) ;

			if ( !file ) cout << endl << "### " << filename << " does not exist! ###" << endl << endl ;
			else {
			//read txt

			while ( file >> data.sid ) {
			  file >> data.sname ;
			  file >> num ; // Ūint
			  data.one = (unsigned char) num ; //�૬
			  file >> num ;
			  data.two = (unsigned char) num ;
			  file >> num ;
			  data.three = (unsigned char) num ;
			  file >> num ;
			  data.four = (unsigned char) num ;
			  file >> num ;
			  data.five = (unsigned char) num ;
			  file >> num ;
			  data.six = (unsigned char) num ;
			  file >> data.average ;
			  step.push_back(data) ;
			} // while
			file.close() ;

			//change bin
			int i = 0 ;
			char t = '\t' ;
			filename = "input" + filenum + ".bin" ;
			ofstream out ( filename.c_str(), ios::out|ios::binary ) ;
			while ( i < step.size() ) {
				out.write( step[i].sid, sizeof(step[i].sid) ) ;
				out.write( step[i].sname, sizeof(step[i].sname) ) ;
				out.write( (char*)&step[i].one, sizeof(step[i].one) ) ;
				out.write( (char*)&step[i].two, sizeof(step[i].two) ) ;
				out.write( (char*)&step[i].three, sizeof(step[i].three) ) ;
				out.write( (char*)&step[i].four, sizeof(step[i].four) ) ;
				out.write( (char*)&step[i].five, sizeof(step[i].five) ) ;
				out.write( (char*)&step[i].six, sizeof(step[i].six) ) ;
				out.put(0) ; // �O0���O'0'
				out.put(0) ; // �O0���O'0'
				out.write( (char*)&step[i].average, sizeof(step[i].average) ) ;
				i++ ;
			} // while()

			success = true ;
		} // else

		} // Mission0()

		int table_size() {
			int temp = step.size()*1.2 ;
			int n ;
			int i ;

			n = temp + 1;
			while(1){
				for(i = 2 ; i < n / 2; i++ ){
					if( n % i == 0){
						break;
					} // if
 				} // for

				if( i >= ( n / 2 ) ){
					break;
				} // if

				n++;
			} // while

			return n ;

		} // table_size()

		int highestStep() { // �̰��B��
			int temp = step.size() / 3 ;
			int n ;
			int i ;

			n = temp + 1;
			while(1){
				for(i = 2 ; i < n / 2 ;i++){
					if( n % i== 0){
						break;
					} // if
 				} // for

				if( i >= (n/2) ){
					break;
				} // if

				n++;
			} // while

			return n ;

		} // highestStep()

		int hashValue( int i, int size ) { // �����
			long long int a = 1 ;
			long long int temp ;
			for ( int j = 0 ; step[i].sid[j] != '\0' ; j++ ) {
			  temp = step[i].sid[j]  ;
			  a = a * temp ;
			} // for

			a = a % size ;
			return a ;
		} // hashValue()

		int hash2( int i ) { // �ĤG���
			int hs = highestStep() ;

			long long int a = 1 ;
			long long int temp ;
			for ( int j = 0 ; step[i].sid[j] != '\0' ; j++ ) {
			  temp = step[i].sid[j]  ;
			  a = a * temp ;
			} // for

			a = hs-( a % hs ) ;
			return a ;

		} // hash2()

		void Mission1( string & filenum ){
			dataget( filenum ) ;
			int size = table_size() ;
			DATA X[size] ;
			//successful number
			double sall = 0.0 ;
			double snum = 1.0 ;
			//unsuccessful number
			double usall = 0.0 ;
			double usnum = 0.0 ;

			for ( int i = 0 ; i < step.size() ; i++ ) {
				step[i].hvalue = hashValue(i, size) ;
				snum = 1.0 ;
				for ( int j = step[i].hvalue ; true ; j++ ) {
					if ( X[j].sid[0] == '\0' ) {
						X[j] = step[i] ;
						sall = snum + sall ;
						break ;
					} // if
					if ( j == size - 1 ) {
						j = -1 ;
					} // if

					snum++ ;
				} // for
			} // for

			//unsuccessful search
			for ( int i = 0 ; i < size ; i++ ) {
				usnum = 0.0 ;
				for ( int j = i ; X[j].sid[0] != '\0' ; j++ ) {
					if ( j == size-1 ) j = -1 ;
					usnum++ ;
				} // for
				usall = usnum + usall ;
			} // for
			
			
			/*
			// time successful search
			double start = clock() ;
			for ( int i = 0 ; i < step.size() ; i++ ) {
				for ( int j = step[i].hvalue ; strcmp( X[j].sid, step[i].sid ) != 0  ; j++ ) if ( j = size-1 ) j = -1 ;
				
			} // for()
			double end = clock() ;
			
			
			cout << " average time : " << (end - start) / CLOCKS_PER_SEC << endl ;
			*/
			
			sall = sall/step.size() ;
			usall = usall/size;
			//screen watch
			cout << "Hash Table X has been created." << endl << endl  ;
			cout << "unsuccessful search: " << usall << " comparised on average" << endl << endl ;
			cout << "successful search: " << sall << " comparised on average" << endl << endl ;




			//make file

			string filename = "linear" + filenum + ".txt" ;
			if ( size == 0 ) cout << "error" << endl ;
			else {
				fstream file ;
				file.open( filename.c_str(), ios::out ) ;
				file << " --- Hash Table X --- (linear probing)" << "\n" ;
				for ( int i = 0 ; i < size ; i++ ) {
					file << "[" << setw(4) << i << "]" << "\t" ;
					if ( X[i].sid[0] == '\0' ) file << "\n" ;
					else {
						file << X[i].hvalue << "," << "\t" ;
						file << X[i].sid << "," << "\t" ;
						file << X[i].sname << "," << "\t" ;
						file << setw(5) << X[i].average << "\n" ;
					} // else
				} // for
				file.close() ;


			} // else

		} // Mission1()

		void Mission2( string &filenum ){
			int size = table_size() ;
			DATA X[size] ;
			//successful number
			double sall = 0.0 ;
			double snum = 1.0 ;
			int num ;

			for ( int i = 0 ; i < step.size() ; i++ ) {
				step[i].hvalue = hashValue(i, size) ;
				num = hash2( i ) ;
				snum = 1.0 ;
				for ( int j = step[i].hvalue ; true ; j = j + num ) {
					if ( X[j].sid[0] == '\0' ) {
						X[j] = step[i] ;
						sall = snum + sall ;
						break ;
					} // if
					if ( j >= (size - num ) ){
						j = j - (size) ;
					} // if

					snum++ ;
				} // for
			} // for



			sall = sall/step.size() ;
			//screen watch
			cout << "Hash Table Y has been created." << endl << endl  ;
			cout << "successful search: " << sall << " comparised on average" << endl << endl ;

			//make file

			string filename = "double" + filenum + ".txt" ;
			if ( size == 0 ) cout << "error" << endl ;
			else {
				fstream file ;
				file.open( filename.c_str(), ios::out ) ;
				file << " --- Hash Table Y --- (double probing)" << "\n" ;
				for ( int i = 0 ; i < size ; i++ ) {
					file << "[" << setw(4) << i << "]" << "\t" ;
					if ( X[i].sid[0] == '\0' ) file << "\n" ;
					else {
						file << X[i].hvalue << "," << "\t" ;
						file << X[i].sid << "," << "\t" ;
						file << X[i].sname << "," << "\t" ;
						file << setw(5) << X[i].average << "\n" ;
					} // else
				} // for
				file.close() ;


			} // else
		
		} // Mission2()
		
		void Mission3 ( string &filenum ) {
			int size = table_size() ;
			DATA X[size] ;
			//successful number
			double sall = 0.0 ;
			double snum = 0.0 ;
			//unsuccessful number
			double usall = 0.0 ;
			double usnum = 0.0 ;
			for ( int i = 0 ; i < step.size() ; i++ ) {
				step[i].hvalue = hashValue(i, size) ;
				snum = 1.0 ;

				for ( int j = step[i].hvalue ; snum < size + 1 ; j = (step[i].hvalue + (int)pow( snum-1, 2 )) % size ) {
					if ( X[j].sid[0] == '\0' ) {
						X[j] = step[i] ;
						sall = snum + sall ;
						break ;
					} // if

					snum++ ;
				} // for
				if (snum >= size+1 ) garbage.push_back( step[i] ) ;
			} // for

			//unsuccessful search
			int a ;
			for ( int i = 0 ; i < size ; i++ ) {
				usnum = 0.0 ;
				a = 0.0 ;
				for ( int j = i ; X[j].sid[0] != '\0' ; j = ( i + (int)pow( a, 2 ) ) % size ) {
					usnum++ ;
					a++ ;
				} // for
				usall = usnum + usall ;
			} // for
			
			
			/*
			// time successful search
			double start = clock() ;
			double temp = 0.0 ;
			for ( int i = 0 ; i < step.size() ; i++ ) {
				for ( int j = step[i].hvalue ; strcmp( X[j].sid, step[i].sid ) != 0 ; j = (int)( step[i].hvalue +  pow( temp, 2 ) ) % size  ) {
					temp++ ;
				} // for

			} // for()
			double end = clock() ;


			cout << " average time : " << (end - start) / CLOCKS_PER_SEC << endl ;

			*/

			sall = sall/step.size() ;
			usall = usall/size;
			//screen watch
			cout << "Hash Table Z has been created." << endl << endl  ;
			cout << "unsuccessful search: " << usall << " comparised on average" << endl << endl ;
			cout << "successful search: " << sall << " comparised on average" << endl << endl ;




			//make file

			string filename = "quadratic" + filenum + ".txt" ;
			if ( size == 0 ) cout << "error" << endl ;
			else {
				fstream file ;
				file.open( filename.c_str(), ios::out ) ;
				file << " --- Hash Table Z --- (quadratic probing)" << "\n" ;
				for ( int i = 0 ; i < size ; i++ ) {
					file << "[" << setw(4) << i << "]" << "\t" ;
					if ( X[i].sid[0] == '\0' ) file << "\n" ;
					else {
						file << X[i].hvalue << "," << "\t" ;
						file << X[i].sid << "," << "\t" ;
						file << X[i].sname << "," << "\t" ;
						file << setw(5) << X[i].average << "\n" ;
					} // else
				} // for
				file.close() ;


			} // else
			
		} // Mission3()


};



int main() {
	bool one_first = false ;

	string str ;
	bool temp = false ;
	Probe do1 ;
	string filename ;
	while( true ) {
		cout << "*** Hash Table Builder **" << endl ;
		cout << "* 0. QUIT                  *" << endl ;
		cout << "* 1. Linear probing        *" << endl ;
		cout << "* 2. Double hashing        *" << endl ;
		cout << "* 3. Quadratic probing     *" << endl ;
		cout << "*************************************" << endl ;
		cout << "Input a choice(0, 1, 2, 3):" ;
		int command ;
  	  	if ( !do1.Is_num( command ) ) cout << "Command does not exist!" << endl << endl ;
  	 	else if ( command > 3 || command < 0 ) cout << "Command does not exist!" << endl << endl ;
 		else if ( command == 0 ) break ;
  	  	else if ( command == 1 ) {
  	  		one_first = true ;
  	  		do1.Mission1( filename ) ;
  	  	} // else if
  	  	else if ( command == 2 && one_first ) {
			do1.Mission2( filename ) ;
		} // else if
		else if ( command == 3 && one_first ) {
			do1.Mission3( filename ) ;
		} // else if
		else cout << "### Choose 1 first. ###" << endl ;
	} // while
} // main()
