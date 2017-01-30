#include "book.h"


bool Book::pick (std::vector<char> &_ISBN, int user_id)
{
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
                    if (_qnt<1) {std::cout<<"Book is not avaliable at this moment.."<<std::endl; out.close(); return true;}
                    _qnt--;
                    for (int j=0; j<ISBN_size; j++) {ISBN[j]=tmp[j];}
                    itoa(_qnt,qnt,10);
                    out.seekp(offset+(block_size-qnt_size));
                    for (int j=0; j<qnt_size; j++){out<<qnt[j];}
                    out.close();
                    tmp.clear();
                    for (int j=0;j<ISBN_size;j++){
                        tmp.push_back(ISBN[j]);
                    }
                    USER temp;
                    if (!(temp.take(tmp, user_id))) {put(tmp); out.close(); return false;}
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

bool Book::put (std::vector<char> &_ISBN) {
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


            /*if (_qnt==1) {
                out.seekp(offset, std::ios::beg);
                for (int j=0; j<block_size; j++) {out.put(0x00);}
                out.close();
                return true;
            }
            _qnt--;*/
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
