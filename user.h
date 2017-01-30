#ifndef USER_H
#define USER_H
#include <stdio.h>
#include <fstream>
#include <iostream>
#include <vector>
#include <iterator>
#include <string.h>
#include <algorithm>
#include <iomanip>
#include "Book.h"

#define u_list "Users.bin"
#define id_size 4
#define name_size 25
#define Book_size 17
#define bag_size (Book_size * 20)
#define block ((name_size * 2) + id_size + bag_size)



class Book;
class USER {
    char id [id_size] {};
    char name [name_size] {};
    char sname [name_size] {};
    char bag [bag_size] {};

public:
    USER() {}

    bool add (std::vector<char> &v1, std::vector<char> &v2) {
        if (v1.size() > name_size || v2.size() > name_size) {std::cout<<"Name is too large!"<<std::endl; return false;}
        for (unsigned int i=0; i<v1.size(); i++) {
            name[i] = v1[i];
        }
        for (unsigned int i=0; i<v2.size(); i++) {
            sname[i] = v2[i];
        }
        int offset = freespace();

        std::fstream out;
        out.open(u_list,std::ios::binary|std::ios::in|std::ios::out);
        if (!out) {
            std::cout<<"Can't open the file.."<<std::endl;
            return false;
        }
      //  out.seekg (0, out.end);
        int _id=(maxid()+1);
        itoa(_id,id,10);
        out.seekp(0,std::ios::end);
        if (offset>=0) {out.seekp(offset,std::ios::beg);}

        for (int i=0; i<id_size; i++) {out<<id[i];}
        for (int i=0; i<name_size; i++) {out<<name[i];}
        for (int i=0; i<name_size; i++) {out<<sname[i];}
        for (int i=0; i<bag_size; i++) {out<<bag[i];}
        out.close();

        return true;
    }

    bool find (std::vector<char> &v1) {
        if (v1.size() > name_size) {std::cout<<"Input is too large!"<<std::endl; return false;}

        std::ifstream out;
        out.open(u_list,std::ios::binary|std::ios::app);
        if (!out) {
            std::cout<<"Can't open the file.."<<std::endl;
            return false;
        }
        out.seekg (0, out.end);
        int length = out.tellg();

        std::vector<char> tmp;
        std::vector<char>::iterator it;

        out.seekg(0);
        for (int i=0;i<block;i++){
            tmp.push_back(out.get());
        }
        v1.shrink_to_fit();

        int offset {};
        int counter {};
        for (int i=0; i<=(length/block); i++) {
            if ((it=std::search(tmp.begin(),tmp.end(),v1.begin(),v1.end()))!=tmp.end()) {
                for (int j=0; j<id_size; j++) {id[j]=tmp.at(j);}
                int _id = atoi(id);
                std::cout<<"User found. Requested ID: "<<_id<<' '<<"User: ";
                counter++;
                for (int j=(id_size); j<=(id_size+name_size);j++) {if ((tmp.at(j))==0x00) break; std::cout<<tmp.at(j);}
                std::cout<<' ';
                for (int j=(id_size+name_size); j<=((name_size*2)+id_size);j++) {if ((tmp.at(j))==0x00) break; std::cout<<tmp.at(j);}
                std::cout<<std::endl;

            }
            offset=(offset+block);
            out.seekg(offset);
            tmp.clear();
            for (int i=0;i<block;i++){tmp.push_back(out.get());}

        }
       out.close();
       if (counter==0) {return false;}
       return true;
    }

    bool find (int _id);

    int maxid () {
        std::ifstream out;
        out.open(u_list,std::ios::binary);
        if (!out) {
            std::cout<<"Can't open the file.."<<std::endl;
            return false;
        }
        out.seekg (0, out.end);
        int length = out.tellg();
        if (length==0) {return (0);}

        std::vector<char> tmp;

        out.seekg(0);
        for (int i=0;i<block;i++){
            tmp.push_back(out.get());
        }

        int offset {};
        int nxt_id {};
        for (int i=0; i<(length/block); i++) {
            for (int j=0; j<id_size; j++) {id[j]=tmp.at(j);}
            if ((atoi(id))>nxt_id) {nxt_id=(atoi(id));}

            offset=(offset+block);
            out.seekg(offset);
            tmp.clear();
            for (int i=0;i<block;i++){tmp.push_back(out.get());}

        }
        out.close();
        return nxt_id;

    }

    int freespace () {
        std::ifstream out;
        out.open(u_list,std::ios::binary|std::ios::app);
        if (!out) {
            std::cout<<"Can't open the file.."<<std::endl;
            return false;
        }
        out.seekg (0, out.end);
        int length = out.tellg();
        if (length==0) {return (0);}

        std::vector<char> tmp;

        out.seekg(0);
        for (int i=0;i<block;i++){
            tmp.push_back(out.get());
        }

        int offset {};
        for (int i=0; i<(length/block); i++) {
            for (int j=0; j<id_size; j++) {id[j]=tmp.at(j);}
            if ((atoi(id))==0) {out.close(); return offset;}

            offset=(offset+block);
            out.seekg(offset);
            tmp.clear();
            for (int i=0;i<block;i++){tmp.push_back(out.get());}

        }
        out.close();
        return -1;

    }

    bool del (int a) {
        std::fstream out;
        out.open(u_list,std::ios::binary|std::ios::in|std::ios::out);
        if (!out) {
            std::cout<<"Can't open the file.."<<std::endl;
            return false;
        }
        out.seekp((a*block)-block,std::ios::beg);
        for (int i=0; i<block; i++) {out.put(0x00);}
        out.close();
        return true;
    }

    bool take  (std::vector<char> &_ISBN, int user_id) {
        std::fstream out;
        out.open(u_list,std::ios::binary|std::ios::in|std::ios::out);
        if (!out) {
            std::cout<<"Can't open the file.."<<std::endl;
            return false;
        }
        out.seekg (0, out.end);
        int length = out.tellg();
        std::cout<<std::endl;
        std::vector<char> tmp;

        out.seekg(0);
        for (int i=0;i<block;i++){
            tmp.push_back(out.get());
        }

        int offset {};
        int counter {};
        for (int i=0; i<(length/block); i++) {
            for (int j=0; j<id_size; j++) {id[j]=tmp.at(j);}
            if (user_id==(atoi(id))) {
                char temp [Book_size];
                int shift {};
                int counter2 {};
                for (int k=0; k<(bag_size/Book_size); k++) {
                    for (int j = (shift+id_size+(name_size*2)); j<(Book_size+shift+id_size+(name_size*2)); j++) {
                         temp[(j-(shift+id_size+(name_size*2)))]=tmp[j];
                    }

                    for (int j=0; j<Book_size; j++) {
                        if (temp[j]==0x00) {counter++;}
                    }
                    if (counter>=Book_size) {break;}
                    counter=0;
                    shift=shift+Book_size;
                    counter2++;
                }
                if (counter2==(bag_size/Book_size)) { std::cout<<"User's bag is full!! Return some books to be able to take new."<<std::endl; out.close(); return false;}
                out.seekp(offset+shift+id_size+(name_size*2), std::ios::beg);
                for (int k=0; k<Book_size; k++) {
                    out<<_ISBN[k];
                }

                out.close();
                return true;
            }
            offset=(offset+block);
            out.seekg(offset);
            tmp.clear();
            for (int i=0;i<block;i++){tmp.push_back(out.get());}

        }
        out.close();
        return false;

    }

    bool ret (std::vector<char> &_ISBN, int _id);

};

#endif // USER_H
