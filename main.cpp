#include <iostream>

#include "book.h"
#include "user.h"
#include <stdio.h>

using namespace std;

int main()
{
    std::ifstream in;
    in.open(u_list,std::ios::binary|std::ios::app);
    in.seekg (0, in.end);
    int length = in.tellg();
    in.close();
    if ((length%block)!=0) {cout<<"User.bin was damaged. Further processing is not possible."<<endl<<"Delete User.bin and try again."; cin.get(); return 1;};

    std::ifstream in2;
    in2.open(b_list,std::ios::binary|std::ios::app);
    in2.seekg (0, in2.end);
    length = in2.tellg();
    in2.close();
    if ((length%block_size)!=0) {cout<<"Book.bin was damaged. Further processing is not possible."<<endl<<"Delete Book.bin and try again."; cin.get(); return 1;};


    setlocale(LC_ALL, "Russian");
    char main_menu {};
    bool main_menu_flag {false};

    cout <<"HHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHH"<<endl;
    cout <<"HH                                                     HH"<<endl;
    cout <<"HH    HHH    HHH  HHHH   HHHH     H    HHHH   H   H    HH"<<endl;
    cout <<"HH     H      H   H  HH  H  HH   H H   H  HH  H   H    HH"<<endl;
    cout <<"HH     H      H   HHHH   HHHH   H   H  HHHH    HHH     HH"<<endl;
    cout <<"HH     H   H  H   H  HH  H  H   HHHHH  H  H     H      HH"<<endl;
    cout <<"HH     HHHHH HHH  HHHH   H   H  H   H  H   H    H v0.1 HH"<<endl;
    cout <<"HH                                                     HH"<<endl;

    while (!main_menu_flag) {

        cout <<"HHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHH"<<endl;
        cout <<"HH                                                     HH"<<endl;
        cout <<"HH           PRESS 1 TO ADD/DELETE/FIND USER           HH"<<endl;
        cout <<"HH                                                     HH"<<endl;
        cout <<"HH           PRESS 2 TO ADD/DELETE/FIND BOOK           HH"<<endl;
        cout <<"HH                                                     HH"<<endl;
        cout <<"HH           PRESS 3 TO TAKE/RETURN BOOK               HH"<<endl;
        cout <<"HH                                                     HH"<<endl;
        cout <<"HH           PRESS 4 FOR HELP                          HH"<<endl;
        cout <<"HH                                                     HH"<<endl;
        cout <<"HH           PRESS 5 TO QUIT                           HH"<<endl;
        cout <<"HH                                                     HH"<<endl;
        cout <<"HHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHH"<<endl<<endl;

        cout << "Please make your selection: "<<endl;
        cin>>fgets(&main_menu,1,stdin);

        switch (main_menu) {
        case '1': {
                char option {};
                char sec_menu {};
                bool sec_menu_flag {false};

                while (!sec_menu_flag) {
                    system("cls");
                    cout <<"HHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHH"<<endl;
                    cout <<"HH                                                     HH"<<endl;
                    cout <<"HH                                                     HH"<<endl;
                    cout <<"HH                                                     HH"<<endl;
                    cout <<"HH              PRESS 'a' TO ADD USER                  HH"<<endl;
                    cout <<"HH                                                     HH"<<endl;
                    cout <<"HH              PRESS 'd' TO DELETE USER               HH"<<endl;
                    cout <<"HH                                                     HH"<<endl;
                    cout <<"HH              PRESS 'f' TO FIND USER                 HH"<<endl;
                    cout <<"HH                                                     HH"<<endl;
                    cout <<"HH                                                     HH"<<endl;
                    cout <<"HH                                                     HH"<<endl;
                    cout <<"HHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHH"<<endl<<endl;

                    cout<<"Press <a> to add user, <d> to delete user, <f> to find user by name or ID:"<<endl;
                    cin>>fgets(&sec_menu,1,stdin);
                    USER one;

                    switch (sec_menu) {
                    case 'a': {
                       cout<<"Enter user NAME"<<endl;
                       string str;
                       std::fflush(stdin);
                       cin>>str;
                       std::vector<char> name_tmp(str.begin(), str.end());
                       cout<<"Enter user SURNAME"<<endl;
                       std::fflush(stdin);
                       cin>>str;
                       std::vector<char> sname_tmp(str.begin(), str.end());
                       if (!(one.add(name_tmp, sname_tmp))) {
                           cout<<"Ended with error."<<endl;
                           sec_menu=0;
                           sec_menu_flag=true;
                           break;
                       }

                       cout<<"Done!"<<endl;
                       sec_menu=0;
                       sec_menu_flag=true;
                       break;
                    }
                    case 'd': {
                        cout<<"Note: If you dont know user's ID, please use FIND USER option."<<endl;
                        cout<<"Enter user ID to delete user from database:"<<endl;
                        int _userID {};
                        cin>>_userID;
                        if (!(one.find(_userID))) {cout<<"User with ID: "<<_userID<<' '<<"was not found."; sec_menu_flag=true;break;}
                        cout<<"Do you really want to delete user (y/n)? "<<endl;
                        cin>>fgets(&option,1,stdin);
                        if (option=='y') {
                            if (!(one.del(_userID))) {cout<<"User delete operation failed. Try again."<<endl;}
                            cout<<"User deleted.";
                            sec_menu_flag=true; break;
                        }
                        else {cout<<"Ok."<<endl;}
                        sec_menu_flag=true;
                        break;
                    }
                    case 'f': {
                        cout<<"Enter user name or surname to seek for:"<<endl;
                        string str;
                        std::fflush(stdin);
                        cin>>str;
                        std::vector<char> name_tmp(str.begin(), str.end());
                        if (!(one.find(name_tmp))) {
                            cout<<"User was not found."<<endl;
                            sec_menu_flag=true;
                            break;
                        }
                        sec_menu_flag=true;
                        break;
                    }
                    default: /*cout<<"You entered <"<<sec_menu<<'>'<<". Please, check your choise and try again:"<<endl;*/ break;
                  }
                }
                sec_menu=0;
                sec_menu_flag=false;
                cout<<"Do you want to continue work?  y/n "<<endl;
                cin>>fgets(&option,1,stdin);
                if (option!='y') {main_menu_flag=true;}

                break;
}
        case '2': {
            system("cls");
            cout <<"HHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHH"<<endl;
            cout <<"HH                                                     HH"<<endl;
            cout <<"HH                                                     HH"<<endl;
            cout <<"HH                                                     HH"<<endl;
            cout <<"HH              PRESS 'a' TO ADD BOOK                  HH"<<endl;
            cout <<"HH                                                     HH"<<endl;
            cout <<"HH              PRESS 'd' TO DELETE BOOK               HH"<<endl;
            cout <<"HH                                                     HH"<<endl;
            cout <<"HH              PRESS 'f' TO FIND BOOK                 HH"<<endl;
            cout <<"HH                                                     HH"<<endl;
            cout <<"HH                                                     HH"<<endl;
            cout <<"HH                                                     HH"<<endl;
            cout <<"HHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHH"<<endl<<endl;

            char option {};
            char sec_menu {};
            bool sec_menu_flag {false};
            cout<<"Press <a> to add book, <d> to delete book, <f> to find book name or ID:"<<endl;
            while (!sec_menu_flag) {
                cin>>fgets(&sec_menu,1,stdin);
                Book two;
                switch (sec_menu) {
                case 'a': {
                    int year_tmp;
                    string str;
                    cout<<"Enter book's title:"<<endl;
                    std::fflush(stdin);
                    std::getline(std::cin, str);
                    std::vector<char> title_tmp(str.begin(), str.end());
                    cout<<"Enter boook's author:"<<endl;
                    std::fflush(stdin);
                    std::getline(std::cin, str);
                    std::vector<char> author_tmp(str.begin(), str.end());
                    cout<<"Enter book edition's year:"<<endl;
                    cin>>year_tmp;
                    cout<<"Enter unique book's number (ISBN):"<<endl;
                    std::fflush(stdin);
                    std::getline(std::cin, str);
                    std::vector<char> isbn_tmp(str.begin(), str.end());

                    if (two.find(isbn_tmp)) {
                        cout<<"Book already exists! Another one is added!"<<endl<<endl;
                        two.addfast(isbn_tmp);
                        sec_menu_flag=true;
                        break;
                    }

                    if (!(two.add(title_tmp, author_tmp, year_tmp, isbn_tmp))) {cout<<"Ended with error."<<endl;sec_menu_flag=true; break;}

                    cout<<"Done!"<<endl;
                    sec_menu_flag=true;
                    break;
                }
                case 'd': {
                    cout<<"Enter book's ISBN to delete:"<<endl;
                    string str;
                    std::fflush(stdin);
                    cin>>str;
                    std::vector<char> isbn_tmp(str.begin(), str.end());
                    if (!(two.find(isbn_tmp))) {
                        cout<<"Book with ISBN: ";
                        for (unsigned int i=0; i<isbn_tmp.size(); i++) {cout<<isbn_tmp[i];}
                        cout<<" was not found. Check and try again."<<endl;
                        sec_menu_flag=true;
                        break;}
                    cout<<"Do you really want to delete this book? (y/n)? "<<endl;
                    cin>>fgets(&option,1,stdin);
                    if (option=='y') {
                        if (!(two.del(isbn_tmp))) {cout<<"User delete operation failed. Try again."<<endl;}
                        cout<<"Book was deleted.";
                        sec_menu_flag=true; break;
                    }
                    cout<<"Ok!"<<endl;
                    sec_menu_flag=true;
                    break;
                }
                case 'f': {
                    cout<<"Enter book's title, author, or ISBN to seek for:"<<endl;
                    string str;
                    std::fflush(stdin);
                    cin>>str;
                    std::vector<char> name_tmp(str.begin(), str.end());
                    if (!(two.find(name_tmp))) {cout<<"Book not found.."<<endl; sec_menu_flag=true; break;}
                    cout<<"Done!"<<endl;
                    sec_menu_flag=true;
                    break;
                }
                default: cout<<"You entered <"<<sec_menu<<'>'<<". Please, check your choise and try again:"<<endl;
                }
            }
            sec_menu=0;
            sec_menu_flag=false;
            cout<<"Do you want to continue work?  y/n "<<endl;
            cin>>fgets(&option,1,stdin);
            if (option!='y') {main_menu_flag=true;}
            break;

}
        case '3': {
                system("cls");
                cout <<"HHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHH"<<endl;
                cout <<"HH                                                     HH"<<endl;
                cout <<"HH                                                     HH"<<endl;
                cout <<"HH                                                     HH"<<endl;
                cout <<"HH              PRESS 't' TO TAKE BOOK                 HH"<<endl;
                cout <<"HH               FROM LIBRARY TO USER                  HH"<<endl;
                cout <<"HH                                                     HH"<<endl;
                cout <<"HH             PRESS 'r' TO RETURNE BOOK               HH"<<endl;
                cout <<"HH               FROM USER TO LIBRARY                  HH"<<endl;
                cout <<"HH                                                     HH"<<endl;
                cout <<"HH                                                     HH"<<endl;
                cout <<"HH                                                     HH"<<endl;
                cout <<"HHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHH"<<endl<<endl;

                char option {};
                char sec_menu {};
                bool sec_menu_flag {false};
                cout<<"Press <t> to take a book, <r> to return a book:"<<endl;
                while (!sec_menu_flag) {
                    cin>>fgets(&sec_menu,1,stdin);
                    switch (sec_menu) {
                    case 't': {
                        USER user;
                        Book book;
                        string str;
                        int id_tmp;
                        cout<<"Enter User ID:"<<endl;
                        std::fflush(stdin);
                        cin>>id_tmp;
                        if (!(user.find(id_tmp))) {
                            cout<<"User was not found. Use 'FIND' to search for correct ID.";
                            sec_menu_flag=true;
                            break;
                        }
                        cout<<"Enter unique book's number (ISBN):"<<endl;
                        std::fflush(stdin);
                        std::getline(std::cin, str);
                        std::vector<char> isbn_tmp(str.begin(), str.end());
                        if (!(book.pick(isbn_tmp,id_tmp))) {cout<<"Operation failed."<<endl;};
                        cout<<"Done!";
                        sec_menu_flag=true;
                        break;
                    }
                    case 'r': {
                        USER user;
                        Book book;
                        string str;
                        int id_tmp;
                        cout<<"Enter User ID:"<<endl;
                        std::fflush(stdin);
                        cin>>id_tmp;
                        if (!(user.find(id_tmp))) {
                            cout<<"User was not found. Use 'FIND' to search for correct ID.";
                            sec_menu_flag=true;
                            break;
                        }
                        cout<<"Enter unique book's number (ISBN) to return to Library:"<<endl;
                        std::fflush(stdin);
                        std::getline(std::cin, str);
                        std::vector<char> isbn_tmp(str.begin(), str.end());
                        if (!(user.ret(isbn_tmp,id_tmp))) {cout<<"Operation failed."<<endl;};
                        cout<<"Done!";
                        sec_menu_flag=true;
                        break;
                    }
                    default: cout<<"You entered <"<<sec_menu<<'>'<<". Please, check your choise and try again:"<<endl;
                    }
                }
                sec_menu=0;
                sec_menu_flag=false;
                cout<<"Do you want to continue work?  y/n "<<endl;
                cin>>fgets(&option,1,stdin);
                if (option!='y') {main_menu_flag=true;}
                break;
        }
        case '4': {
            char option {};
            cout<<"Help menu is still under construction..."<<endl;
            cout<<"Do you want to continue work?  y/n "<<endl;
            cin>>fgets(&option,1,stdin);
            if (option!='y') {main_menu_flag=true;}
            break;
        }
        case '5': main_menu_flag=true; break;
        default: cout<<"You entered <"<<main_menu<<'>'<<". Please, check your choise and try again:"<<endl;
        }
        system("cls");
    }
    cout << "See you later!" << endl;
    cin.get();
    return 0;
}
