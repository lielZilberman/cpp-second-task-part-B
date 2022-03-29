#include "Notebook.hpp"
#include "Direction.hpp"
#include <iostream>
#include <stdexcept>
using namespace std;  
using namespace ariel;
using ariel::Direction;

const int MAX_ROW_SIZE = 100;
const int MAX_VALID_CHAR = 125;
const int MIN_VALID_CHAR = 32;
const int PASS = 8500;

void checkValidChar(char c){
    if (c < MIN_VALID_CHAR || c > MAX_VALID_CHAR)
    {
        throw invalid_argument("invalid char");
    }
    
}

int checkLength(int len){
    if (len > PASS)
    {
        return 1;
    }
    return 0;
}

void Page::addRows(unsigned int count){
    vector<char>temp;
    for (unsigned int i = 0; i < count; i++)
    {
        for (unsigned int j = 0; j < MAX_ROW_SIZE; j++)
        {
            temp.push_back('_');
        }
        page.push_back(temp);
        Page::currentRow++;
    }
    
}

Page::Page(unsigned int _id, unsigned int row){
    id = _id;
    Page::addRows(row);
}

void Page::write(unsigned int row, unsigned int col, Direction dir, string word){ 
        if (dir == Direction::Horizontal){
            for (unsigned int i = col; i < col + word.length(); i++)
            {
                checkValidChar(word.at(i-col));
                if (page[row][i] != '_')
                {
                    throw invalid_argument("can't write there!");
                }
            
                page[row][i] = word.at(i-col);
            }
        
        } else{

            for (unsigned int i = row; i < row + word.length(); i++)
            {
                checkValidChar(word.at(i-row));
                if (page[i][col] != '_')
                {
                    throw invalid_argument("can't write there!");
                }
            
                page[i][col] = word.at(i-row);
            }
        }
    }


void Page::erase(unsigned int row, unsigned int col, Direction dir, int length){
    if (dir == Direction::Horizontal){
        for (unsigned int i = col; i < col + static_cast<unsigned long>(length); i++)
        {
            page[row][i] = '~';
        }

    } else{
        for (unsigned int i = row; i < row + static_cast<unsigned long>(length); i++)
        {
            page[i][col] = '~';
        }
    }
}

string Page::read(unsigned int row, unsigned int col, Direction dir, int length){
    string ans;
    if (dir == Direction::Horizontal){
        for (unsigned int i = col; i < col + static_cast<unsigned long>(length); i++)
        {
            ans.push_back(page[row][i]);
        }
        
    } else{
        for (unsigned int i = row; i < row + static_cast<unsigned long>(length); i++)
        {
            ans.push_back(page[i][col]);
        }
    }

    return ans;
}



int Notebook::isExist(int pageID){
    for (unsigned int i = 0; i < notebook.size(); i++){
        if (notebook[i].id == pageID){
            return 1;
        }
    }

    return 0;
}

Page Notebook::getPage(int pageID){
    unsigned int ans = 0;
    for (unsigned int i = 0; i < notebook.size(); i++){
        if (notebook[i].id == pageID){
           ans = i;
        } 
    } 
    return notebook[ans];
}

void Notebook::swap(int pageID, const Page& p){
    for (unsigned int i = 0; i < notebook.size(); i++)
    {
        if (notebook[i].id == pageID)
        {
            notebook.erase(notebook.begin()+i);
            break;
        }
        
    }
    notebook.push_back(p);
}

void checkValidInput(int pageID, int row, int col, Direction dir, int len){
    if (pageID < 0 || row < 0 || col < 0 || len < 0 || ((dir == Direction::Horizontal) && (len + col > MAX_ROW_SIZE)) || ((dir == Direction::Vertical) && (col+1 > MAX_ROW_SIZE))){
        throw invalid_argument("bad input");
    }
    
}

void Notebook::write(int pageID, int row, int col, Direction dir, const string& word){
    if (checkLength(word.length()) != 0)
            {

        }
    else{    
    checkValidInput(pageID, row, col, dir, word.length());
    if (isExist(pageID) == 0){
        if (dir == Direction::Vertical){
            Page temp(static_cast<unsigned long>(pageID),static_cast<unsigned long>(row) + word.length());
            notebook.push_back(temp);
        }
        else {
            Page temp(static_cast<unsigned long>(pageID),static_cast<unsigned long>(row));
            notebook.push_back(temp);
            }
    }
    Page current = getPage(pageID);
    if (current.currentRow < static_cast<unsigned long>(row) + word.length()){
        current.addRows((static_cast<unsigned long>(row) + word.length()) - (static_cast<unsigned long>(current.currentRow)));
    }
    current.write(static_cast<unsigned long>(row), static_cast<unsigned long>(col), dir, word);
    swap(pageID, current);
}
}

string Notebook::read(int pageID, int row, int col, Direction dir, int len){
    checkValidInput(pageID, row, col, dir, len);
    if (isExist(pageID) == 0){
        if (dir == Direction::Vertical){
            Page temp(static_cast<unsigned long>(pageID),static_cast<unsigned long>(row + len));
            notebook.push_back(temp);
        }
        else {
            Page temp(static_cast<unsigned long>(pageID),static_cast<unsigned long>(row));
            notebook.push_back(temp);
            }
    }
    Page current = getPage(pageID);
    if (current.currentRow < row + len){
        current.addRows(static_cast<unsigned long>((row + len) - (current.currentRow)));
    }
    return current.read(static_cast<unsigned long>(row), static_cast<unsigned long>(col), dir, len);
}

void Notebook::erase(int pageID, int row, int col, Direction dir, int len){
    checkValidInput(pageID, row, col, dir, len);
    if (isExist(pageID) == 0){
        if (dir == Direction::Vertical){
            Page temp(static_cast<unsigned long>(pageID),static_cast<unsigned long>(row + len));
            notebook.push_back(temp);
        }
        else {
            Page temp(static_cast<unsigned long>(pageID),static_cast<unsigned long>(row));
            notebook.push_back(temp);
            }
    }
    Page current = getPage(pageID);
    if (current.currentRow < row + len){
        current.addRows(static_cast<unsigned long>((row + len) - (current.currentRow)));
    }

    current.erase(static_cast<unsigned long>(row), static_cast<unsigned long>(col), dir, len);
    swap(pageID, current);
}
void Notebook::show(int pageID){
    if (pageID < 0)
    {
        throw invalid_argument("you can't see a negative page!");
    }
    
    Page temp = getPage(pageID);
    for (unsigned int i = 0; i < temp.page.size(); i++)
    {
        cout << i << ':' << ' ';
        for (unsigned int j = 0; j < MAX_ROW_SIZE; j++)
        {
            cout << temp.page[i][j];
        }
        cout << endl;
    }
    
    
}