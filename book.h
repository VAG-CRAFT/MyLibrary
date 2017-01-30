#ifndef Book_H
#define Book_H

#include <stdio.h>
#include <fstream>
#include <iostream>
#include <vector>
#include <iterator>
#include <string.h>
#include <algorithm>
#include "user.h"

#define ISBN_size 17
#define def_size 25
#define qnt_size 3
#define year_size 4
#define block_size (ISBN_size+2*def_size+qnt_size+year_size)

#define b_list "Books.bin"

class USER;
class Book {
        char ISBN [ISBN_size] {};
        char qnt [qnt_size] {};
        char year[year_size] {};
        char title [def_size] {};
        char author [def_size] {};

    public:
        Book() {}

        bool add (std::vector<char> &_title, std::vector<char> &_author, int _year, std::vector<char> &_ISBN) {
            if (_title.size() > def_size || _author.size() > def_size) {std::cout<<"Name is too large!"<<std::endl; return false;}
            if (_ISBN.size() > ISBN_size) {std::cout<<"ISBN is too large!"<<std::endl; return false;}
            if (_year>9999 || _year<=0) {std::cout<<"Year is non-valid!"<<std::endl; return false;}
            int offset = freespace();
            for (unsigned int i=0; i<_title.size(); i++) {
                title[i] = _title[i];
            }
            for (unsigned int i=0; i<_author.size(); i++) {
                author[i] = _author[i];
            }
            for (unsigned int i=0; i<_ISBN.size(); i++) {
                ISBN[i] = _ISBN[i];
            }

            std::fstream out;
            out.open(b_list,std::ios::binary|std::ios::in|std::ios::out);
            if (!out) {
                std::cout<<"Can't open the file.."<<std::endl;
                return false;
            }
            out.seekg (0, out.end);
            //int length = out.tellg();

            if (offset>0) {out.seekp(offset,std::ios::beg);}
            for (int i=0; i<ISBN_size; i++) {out<<ISBN[i];}
            for (int i=0; i<def_size; i++) {out<<title[i];}
            for (int i=0; i<def_size; i++) {out<<author[i];}
            itoa(_year,year,10);
            for (int i=0; i<year_size; i++) {out<<year[i];}
            int _qnt=1;
            itoa(_qnt,qnt,10);
            for (int i=0; i<qnt_size; i++) {out<<qnt[i];}
            out.close();

            return true;
        }

        bool addfast (std::vector<char> &_ISBN) {
            std::fstream out;
            out.open(b_list,std::ios::binary|std::ios::in|std::ios::out);
            if (!out) {
                std::cout<<"Can't open the file.."<<std::endl;
                return false;
            }
            out.seekg (0, out.end);
            int length = out.tellg();

            std::vector<char> tmp;
            std::vector<char>::iterator it;

            out.seekg(0);
            for (int i=0;i<block_size;i++){
                tmp.push_back(out.get());
            }

            int offset {};
            for (int i=0; i<=(length/block_size); i++) {
                if ((it=std::search(tmp.begin(),tmp.end(),_ISBN.begin(),_ISBN.end()))!=tmp.end()) {
                    for (int j=(block_size-qnt_size); j<block_size; j++) {qnt[(j-(block_size-qnt_size))]=tmp[j];}
                    int _qnt = atoi(qnt);
                    _qnt++;
                    itoa(_qnt,qnt,10);
                    out.seekp(offset+(block_size-qnt_size));
                    for (int j=0; j<qnt_size; j++){out<<qnt[j];}
                    out.close();
                    return true;
                }
                offset=(offset+block_size);
                out.seekg(offset);
                tmp.clear();
                for (int i=0;i<block_size;i++){tmp.push_back(out.get());}
            }
            out.close();
            return false;
        }

        bool find (const std::vector<char> &v1, int mode = 0) {
            if (v1.size() > def_size) {std::cout<<"Input is too large!"<<std::endl; return false;}

            std::ifstream out;
            out.open(b_list,std::ios::binary);
            if (!out) {
                std::cout<<"Can't open the file.."<<std::endl;
                return false;
            }
            out.seekg (0, out.end);
            int length = out.tellg();



            std::vector<char> tmp;
            std::vector<char>::iterator it;

            out.seekg(0);
            for (int i=0;i<block_size;i++){
                tmp.push_back(out.get());
            }

            //v1.shrink_to_fit();

            int offset {};
            int counter {};

            for (int i=0; i<(length/block_size); i++) {
                if ((it=std::search(tmp.begin(),tmp.end(),v1.begin(),v1.end()))!=tmp.end()) {
                    if (mode==0) {std::cout<<"Book found: "<<std::endl;} std::cout<<"ISBN: ";
                    for (int j=0; j<ISBN_size; j++) { if ((tmp.at(j))==0x00) break; std::cout<<tmp.at(j);}
                    std::cout<<std::endl<<"Book: ";
                    counter++;
                    for (int j=ISBN_size; j<(ISBN_size+def_size);j++) {if ((tmp.at(j))==0x00) break; std::cout<<tmp.at(j);}
                    std::cout<<std::endl<<"Author: ";
                    for (int j=(ISBN_size+def_size); j<=((ISBN_size+(def_size*2)));j++) {if ((tmp.at(j))==0x00) break; std::cout<<tmp.at(j);}
                    if (mode==0) {std::cout<<std::endl<<"Quantity: ";
                        for (int j=(block_size-qnt_size); j<block_size; j++) {std::cout<<tmp[j];}
                    }

                    std::cout<<std::endl<<std::endl;

                }
                offset=(offset+block_size);
                out.seekg(offset);
                tmp.clear();
                for (int k=0;k<block_size;k++){tmp.push_back(out.get());}

            }
           out.close();
           if (counter==0) {return false;}
           return true;
        }

        bool del (std::vector<char> &_ISBN) {
            std::fstream out;
            out.open(b_list,std::ios::binary|std::ios::in|std::ios::out);
            if (!out) {
                std::cout<<"Can't open the file.."<<std::endl;
                return false;
            }
            out.seekg (0, out.end);
            int length = out.tellg();

            std::vector<char> tmp;
            std::vector<char>::iterator it;

            out.seekg(0);
            for (int i=0;i<block_size;i++){
                tmp.push_back(out.get());
            }

            int offset {};
            for (int i=0; i<=(length/block_size); i++) {
                if ((it=std::search(tmp.begin(),tmp.end(),_ISBN.begin(),_ISBN.end()))!=tmp.end()) {
                    for (int j=(block_size-qnt_size); j<block_size; j++) {qnt[(j-(block_size-qnt_size))]=tmp[j];}
                    int _qnt = atoi(qnt);
                    if (_qnt==1) {
                        out.seekp(offset, std::ios::beg);
                        for (int j=0; j<block_size; j++) {out.put(0x00);}
                        out.close();
                        return true;
                    }
                    _qnt--;
                    itoa(_qnt,qnt,10);
                    out.seekp(offset+(block_size-qnt_size));
                    for (int j=0; j<qnt_size; j++){out<<qnt[j];}
                    out.close();
                    return true;
                }
                offset=(offset+block_size);
                out.seekg(offset);
                tmp.clear();
                for (int i=0;i<block_size;i++){tmp.push_back(out.get());}
            }
            out.close();
            return false;
        }

        bool pick (std::vector<char> &_ISBN, int user_id);

        bool put (std::vector<char> &_ISBN);

        int freespace () {
            std::ifstream out;
            out.open(b_list,std::ios::binary|std::ios::app);
            if (!out) {
                std::cout<<"Can't open the file.."<<std::endl;
                return false;
            }
            out.seekg (0, out.end);
            int length = out.tellg();
            if (length==0) {return (0);}

            std::vector<char> tmp;

            out.seekg(0);
            for (int i=0;i<block_size;i++){
                tmp.push_back(out.get());
            }
            char _ISBN[ISBN_size];
            int offset {};
            for (int i=0; i<(length/block_size); i++) {
                for (int j=0; j<ISBN_size; j++) {_ISBN[j]=tmp.at(j);}

                if ((atoi(_ISBN))==0) {out.close(); return offset;}

                offset=(offset+block_size);
                out.seekg(offset);
                tmp.clear();
                for (int i=0;i<block_size;i++){tmp.push_back(out.get());}

            }
            out.close();
            return 0;

        }
};

#endif // Book_H
