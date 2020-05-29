#include "interpreter.h"
#include "../DB/DB.h"

#include <sstream>
#include <fstream>

using namespace ParserModule;

Interpreter::Interpreter(const std::string& filenameDB, const std::string& filenameScript) :
    m_commands(),
    m_scanner(*this),
    m_parser(m_scanner, *this),
    m_location(0)
{
    db = new DB::DB();
    db->loadDB(filenameDB);

    ifs.open(filenameScript, std::ios::in);
    this->switchInputStream(&ifs);
}

Interpreter::Interpreter(const std::string &filenameDB) :
        m_commands(),
        m_scanner(*this),
        m_parser(m_scanner, *this),
        m_location(0)
{
    db = new DB::DB();
    db->loadDB(filenameDB);
}

Interpreter::Interpreter(DB::DB *database) :
        m_commands(),
        m_scanner(*this),
        m_parser(m_scanner, *this),
        m_location(0),
        db(database)
{
}

std::string Interpreter::parse() {
    m_location = 0;
    int res = m_parser.parse();
    std::string ans;
    if (res == 0) {
        ans = this->execute();
    } else {
        ans = "Bad script\n";
    }
    return ans;
}

void Interpreter::clear() {
    m_location = 0;
    m_commands.clear();
}

// std::string Interpreter::str() const {
//     std::stringstream s;
//     s << "Interpreter: " << m_commands.size() << " commands received from command line." << endl;
//     for(int i = 0; i < m_commands.size(); i++) {
//         s << " * " << m_commands[i].str() << endl;
//     }
//     return s.str();
// }

std::string Interpreter::execute() {
    std::string str;
    for (auto op : m_commands) {
        str += op->execute(db);
    }
    return str;
}

void Interpreter::switchInputStream(std::istream *is) {
    m_scanner.switch_streams(is, nullptr);
    m_commands.clear();    
}

// void Interpreter::addCommand(const Command &cmd)
// {
//     m_commands.push_back(cmd);
// }

void Interpreter::add_operation(AST::Operation* op) {
    m_commands.push_back(op);
}

void Interpreter::increaseLocation(unsigned int loc) {
    m_location += loc;
    //cout << "increaseLocation(): " << loc << ", total = " << m_location << endl;
}

unsigned int Interpreter::location() const {
    return m_location;
}

Interpreter::~Interpreter() {
    db->unloadDB();
    delete db;
}




