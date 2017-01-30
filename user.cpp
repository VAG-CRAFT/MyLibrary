#include "user.h"


bool USER::find(int _id)
{
        std::ifstream out;
        out.open(u_list,std::ios::binary|std::ios::app);
        if (!out) {
            std::cout<<"Can't open the file.."<<std::endl;
            return false;
        }
        out.seekg (0, out.end);
        int length = out.tellg();

        std::vector<char> tmp;

        out.seekg(0);
        for (int i=0;i<block;i++){
            tmp.push_back(out.get());
        }

        int offset {};
        for (int i=0; i<(length/block); i++) {
            for (int j=0; j<id_size; j++) {id[j]=tmp.at(j);}
            if (_id==(atoi(id))) {
                std::cout<<"User found. Requested ID: "<<_id<<' '<<"User: ";
                for (int j=(id_size); j<=(id_size+name_size);j++) {if ((tmp.at(j))==0x00) break; std::cout<<tmp.at(j);}
                std::cout<<' ';
                for (int j=(id_size+name_size); j<=((name_size*2)+id_size);j++) {if ((tmp.at(j))==0x00) break; std::cout<<tmp.at(j);}
                std::cout<<std::endl<<std::endl;

                std::vector<char> isbn_tmp {};
                isbn_tmp.reserve(Book_size);
                int shift {};
                int counter {};
                Book tempr;
                for (int k=0; k<(bag_size/Book_size); k++) {
                    for (int j = (shift+id_size+(name_size*2)); j<(Book_size+shift+id_size+(name_size*2)); j++) {
                        isbn_tmp.push_back(tmp[j]);
                    }
                    for (int j=0; j<Book_size; j++) {
                        if (isbn_tmp[j]==0x00) {counter++;}
                    }
                    if (!(counter==17)) {std::cout<<"Requested user has already had book: "<<std::endl; tempr.find(isbn_tmp, 1);}
                    isbn_tmp.clear();
                    counter=0;
                    shift=shift+Book_size;
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

bool USER::ret (std::vector<char> &_ISBN, int _id) {
    std::fstream out;
    out.open(u_list,std::ios::binary|std::ios::in|std::ios::out);
    if (!out) {
        std::cout<<"Can't open the file.."<<std::endl;
        return false;
    }
    out.seekg (0, out.end);
    int length = out.tellg();

    std::vector<char> tmp;

    out.seekg(0);
    for (int i=0;i<block;i++){
        tmp.push_back(out.get());
    }

    int offset {};
    for (int i=0; i<(length/block); i++) {
        for (int j=0; j<id_size; j++) {id[j]=tmp.at(j);}
        if (_id==(atoi(id))) {  //user found here

            while ((_ISBN.size())<Book_size) {_ISBN.push_back(0x00);}
            int shift {};
            std::vector<char> isbn_tmp {};
            isbn_tmp.reserve(Book_size);
            int counter {};
            Book tmp2;
            for (int k=0; k<(bag_size/Book_size); k++) {
                for (int j = (shift+id_size+(name_size*2)); j<(Book_size+shift+id_size+(name_size*2)); j++) {
                    isbn_tmp.push_back(tmp[j]);
                }
                for (int j=0; j<Book_size; j++) {
                    if (_ISBN[j]==isbn_tmp[j]) {counter++;}
                }
                if (counter==17) {
                    out.seekp(offset+shift+id_size+(name_size*2),std::ios::beg);
                    for (int j=0; j<Book_size; j++) {out.put(0x00);}
                    if (!(tmp2.put(_ISBN))) {out.close(); return false;}
                    std::cout<<"Book was succesfully returned."<<std::endl; out.close(); return true;
                }
                isbn_tmp.clear();
                counter=0;
                shift=shift+Book_size;
            }

            std::cout<<"User has no book with requested ISBN number. Check and try again"<<std::endl;
            out.close();
            return false;
        }
        offset=(offset+block);
        out.seekg(offset);
        tmp.clear();
        for (int i=0;i<block;i++){tmp.push_back(out.get());}

    }
    out.close();
    return false;
}
