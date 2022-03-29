#include "Direction.hpp"
#include <string>
#include <vector>

namespace ariel{
class Page{
    public:
        unsigned int id;
        int currentRow = 0;
        std::vector<std::vector<char>>page;
        Page();
        Page(unsigned int _id, unsigned int row);
        void write(unsigned int row, unsigned int col, Direction dir, std::string word);
        std::string read(unsigned int row, unsigned int col, Direction dir, int length);
        void erase(unsigned int row, unsigned int col, Direction dir, int length);
        void addRows(unsigned int count);

};
class Notebook{
    public:
        std::vector<Page>notebook;
        void write(int pageID, int row, int col, Direction dir, const std::string& word);
        std::string read(int pageID, int row, int col, Direction dir, int length);
        void erase(int pageID, int row, int col, Direction dir, int length);
        void show(int pageID);
        int isExist(int pageID);
        void swap(int pageID, const Page& page);
        Page getPage(int pageID);
    };
}