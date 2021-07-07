// Created by rng70

#ifndef COMPILER_SYMBOLTABLE_H
#define COMPILER_SYMBOLTABLE_H

class SymbolTable {
    int sizeOfTable;
    ScopeTable *currentScope;
public:
    explicit SymbolTable(int size) {
        this->sizeOfTable = size;
        currentScope = new ScopeTable(sizeOfTable);
    }

    void setCurrentScope(ScopeTable *p) {
        this->currentScope = p;
    }

    ScopeTable *getCurrentScope() {
        return this->currentScope;
    }

    // required methods for offline
    void EnterScope(FILE *f) {
        ScopeTable *newScopeTable = new ScopeTable(this->sizeOfTable, currentScope->getTableIdTracker());
        // Increment the table tracker value
        currentScope->setTableIdTracker();
        ScopeTable *parentScope = currentScope;
        currentScope = newScopeTable;
        currentScope->setParentScope(parentScope);
        // fprintf(f,"New ScopeTable with Id %d created\n",newScopeTable->getStringifyID().c_str());
    }

    void ExitScope(FILE *f) {
        //currentScope->setTableIdTracker();
        ScopeTable *temp = currentScope;
        currentScope = temp->getParentScope();
        // fprintf(f,"ScopeTable with ID %d removed\n",temp->getStringifyID().c_str());
        delete temp;
    }

    bool Insert(std::string s, std::string type) {
        if (currentScope->Insert(s, type))
            return true;
        return false;
    }
    bool InsertModified(SymbolInfo* s)
    {
        return currentScope->InsertModified(s);
    }

    bool Remove(std::string s) {
        if (currentScope->Delete(s))
            return true;
        return false;
    }

    SymbolInfo *LookUp(std::string s) {
        ScopeTable *temp = currentScope;
        SymbolInfo *yolo;

        while (temp != 0) {
            yolo = temp->LookUP(s);
            if (yolo != 0)
                return yolo;
            temp = temp->getParentScope();
        }
        return 0;
    }

    SymbolInfo* currentScopeLookUp(std::string Name){
        SymbolInfo* result;
        result = currentScope->LookUP(Name);

        if(result!=0) 
            return result;
        return 0;
    }

    void printCurrentScopeTable(FILE *f) {
        currentScope->printModified(f);
    }

    void printAllTable(FILE* f) {
        ScopeTable *recursive = currentScope;
        while (recursive != 0) {
            recursive->printModified(f);
            recursive = recursive->getParentScope();
        }
    }

    ~SymbolTable() {
        ScopeTable *child, *parent;
        child = currentScope;

        while (child != 0) {
            parent = child->getParentScope();
            //child->printModified();
            delete child;
            //child->~ScopeTable();
            child = parent;
        }
        //child->printModified();
        delete child;
        //parent->printModified();
        delete parent;
    }
};

#endif //COMPILER_SYMBOLTABLE_H
