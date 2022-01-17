// WordPuzzle.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <string>
#include <algorithm>
#include <istream>
#include <fstream>
#include <unordered_set>

const char* bigTable[25] = {
        "ELECAPEXMULTRAYAPOPYR",
        "ROVERUZZDNOIPLICAXISA",
        "HCENTERLIFFEREOETCOPM",
        "OUNTEOSEVIVEENCEIONEI",
        "MSUUXMIDECIPENTAPORPD",
        "BUMODUXONUMEREAGONOIO",
        "TSBISLTIPLAFACEOIPUNU",
        "EIEDEARALELSTIONNANAN",
        "TFRACTIRADIUSLOPTRDTC",
        "RAPATWOIGRAMIDPOHALEE",
        "AHPTTENTHMEENOEIIRLSS",
        "TEOWERNOPATTERNNTDENT",
        "IDUOSQUARTICTWORKSLOG",
        "ORPZSCALEHEIAONEBASER",
        "NOPPEARITRMRCLESASENA",
        "INLAMRECHEATTOEIDENTM",
        "EGCHOMMANGSEVENTEENTH",
        "FOURREEDGLEXEDCURREYT",
        "INETDASDEECPONENVOGAU",
        "FPRESSURESOMINUTELURS",
        "TWOENEMWINNPNIAIMULDS",
        "EHEXAGMENTDIETRREMARC",
        "EPLATONICSOVSPCNTERTE",
        "NRATHEIGHTUIDECIMALON",
        "MOBABILITYVERRCENTENT" };

struct point {
    point(int pX, int pY) { x = pX; y = pY; }
    int x;
    int y;
};

char getChar(int x, int y);
void recursiveSearch(const char* pTerm, point location, bool north, bool south, bool east, bool west, const point& p_origin, const char *p_term);
void findWord(const char* p_term);
std::unordered_set<std::string> s_found_words;

int main(int argC, const char** argv)
{
    if (argC != 2) {
        std::cout << "instructions" << std::endl;
        return 0;
    }
    std::cout << argv[1] << std::endl;
    std::string caseProblem(argv[1]);
    std::transform(caseProblem.begin(), caseProblem.end(), caseProblem.begin(), ::toupper);
    if (caseProblem.find(".")) {
        std::ifstream file;
        file.open(argv[1]);
        std::string t_term;
        while ( file >> t_term) {
            if (t_term.length() < 3) {
                continue;
            }
            std::transform(t_term.begin(), t_term.end(), t_term.begin(), ::toupper);
            findWord(t_term.c_str());
        }
    }
    else {
        findWord(caseProblem.c_str());
    }
    return 0;
}

void findWord(const char *p_term) {
    for (int i = 0; i < 25; i++) {
        for (int j = 0; j < 21; j++) {
            recursiveSearch(p_term, point(j, i), true, true, true, true, point(j, i), p_term);
        }
    }

}

void recursiveSearch(const char* pTerm, point location, bool north, bool south, bool east, bool west, const point& p_origin, const char *p_original) {

    if (*pTerm == 0) {
        return;
    }
    if (pTerm[0] != getChar(location.x, location.y)) {
        return;
    }
    if (*(pTerm + 1) == 0) {
        if (s_found_words.find(p_original) == s_found_words.end()) {
            s_found_words.insert(p_original);
            std::cout << p_original << " found at x=" << p_origin.x << " y=" << p_origin.y << std::endl;
        }
        return;
    }
    if (north) {
        recursiveSearch(pTerm + 1, point(location.x, location.y - 1), north, false, east, west, p_origin, p_original);
    }
    if (south) {
        recursiveSearch(pTerm + 1, point(location.x, location.y + 1), false, south,  east, west, p_origin, p_original);
    }
    if (east) {
        recursiveSearch(pTerm + 1, point(location.x + 1, location.y), north, south, east, false, p_origin, p_original);
    }
    if (west) {
        recursiveSearch(pTerm + 1, point(location.x - 1, location.y), north, south, false, west, p_origin, p_original);
    }
}

char getChar(int x, int y) {
    if (y < 0) {
        return 0;
    }
    if (y >= 25) {
        return 0;
    }
    if (x < 0) {
        return 0;
    }
    if (x >= 21) {
        return 0;
    }

    const char* word = bigTable[y];
    return word[x];
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
