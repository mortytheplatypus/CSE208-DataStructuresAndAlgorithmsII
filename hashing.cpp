#include <bits/stdc++.h>
using namespace std;

#define LEN 10000
#define CAPACITY 19841
#define NULLSTRING "0000000\0"

void WordGenerator(string[], int);
int keyFinder(string, string[]);

void SeparateChainingInsert(string[], vector< vector<string> >&, vector< vector<string> >&);
void DoubleHashingInsert(string[], vector<string>&, vector<string>&);
void CustomProbingInsert(string[], vector<string>&, vector<string>&);

void SeparateChainingSearch(string[], vector< vector<string> >&, vector< vector<string> >&);
void DoubleHashingSearch(string[], vector<string>&, vector<string>&);
void CustomProbingSearch(string[], vector<string>&, vector<string>&);

void SeparateChainingDelete(string, string[], vector< vector<string> >&, vector< vector<string> >&);
void DoubleHashingDelete(string, string[], vector<string>&, vector<string>&);
void CustomProbingDelete(string, string[], vector<string>&, vector<string>&);

int Hash1(string);
int Hash2(string);
int auxHash(string);

int main() {
    string words[LEN]; //7-character-long words, having meaning is not necessary
    WordGenerator(words, LEN); //position of the word will serve as key 
    
    vector< vector<string> > separateChain1(CAPACITY), separateChain2(CAPACITY);
    vector<string> doubleHashTable1(CAPACITY, NULLSTRING), doubleHashTable2(CAPACITY, NULLSTRING);
    vector<string> cpTable1(CAPACITY, NULLSTRING), cpTable2(CAPACITY, NULLSTRING);

    SeparateChainingInsert(words, separateChain1, separateChain2);
    DoubleHashingInsert(words, doubleHashTable1, doubleHashTable2);
    CustomProbingInsert(words, cpTable1, cpTable2);

    SeparateChainingSearch(words, separateChain1, separateChain2);
    DoubleHashingSearch(words, doubleHashTable1, doubleHashTable2);
    CustomProbingSearch(words, cpTable1, cpTable2);

    return 0;
}

int Hash1(string word) {
    int multipliers[] = {17, 13, 11, 7, 5, 3, 2}; 
    int temp = 0;
    for (int i=0; i<7; i++) {
        int powerofTen = 1;
        for (int j=0; j<i; j++) {
            powerofTen *= 10;
        }
        temp += multipliers[i]*(word[i])*powerofTen;
    }

    return temp%CAPACITY;
}

int Hash2(string word) {
    int multipliers[] = {31, 71, 67, 53, 97, 23, 83};
    int temp = 0;

    for (int i=0; i<7; i++) {
        int n = 0;
        for (int j=0; j<7; j++) {
            if (j==i) {
                continue;
            }
            n += (word[j]);
        }
        n *= word[i];
        n *= multipliers[i];
        n -= (i%2)*n; 
        //changing it into n -= (i%2)*n*n; changes Hash1() collisions(!!!)
        temp += n;
    }

    return temp%CAPACITY;
}

int auxHash(string word) {
    int multipliers[] = {2, 3, 5, 7, 11, 15, 17};

    int temp = 0;
    for (int i=0; i<7; i++) {
        temp += (word[i]-'a')*multipliers[i];
        temp *= multipliers[i];
    }
    return temp%CAPACITY;
}

//Insertion
void SeparateChainingInsert(string words[], vector< vector<string> >&separateChain1, vector< vector<string> >&separateChain2) {
    int collisions1=0, collisions2=0; 

    for (int i=0; i<LEN; i++) {
        int hash1 = Hash1(words[i]), hash2 = Hash2(words[i]);
        if (separateChain1[hash1].size()!=0) {
            collisions1++;
        }
        separateChain1[hash1].push_back(words[i]);

        if (separateChain2[hash2].size()!=0) {
            collisions2++;
        }
        separateChain2[hash2].push_back(words[i]);
    }
    cout << "Separate Chaining Insertion:\n";
    cout << "\tCollisions by Hash1(): " << collisions1 << "\n";
    cout << "\tCollisions by Hash2(): " << collisions2 << "\n\n";
}

void DoubleHashingInsert(string words[], vector<string>&doubleHashTable1, vector<string>&doubleHashTable2) {
    //doubleHash(k, i) = (Hash(k) + i * auxHash(k)) % N
    int hash, collisions1=0, collisions2=0;

    //Hash1()
    for (int i=0; i<LEN; i++) {
        hash = Hash1(words[i]) % CAPACITY;
        if (doubleHashTable1[hash]==NULLSTRING) {
            doubleHashTable1[hash] = words[i];
        } else {
            collisions1++;
            int j=1, tmp, auxHashValue = auxHash(words[i]);
            while (true) {
                tmp = (hash + j*auxHashValue) % CAPACITY;
                if (doubleHashTable1[tmp]==NULLSTRING) {
                    doubleHashTable1[tmp] = words[i];
                    break;
                }
                collisions1++;
                j++;
            }
        }
    }

    //Hash2()
    for (int i=0; i<LEN; i++) {
        hash = Hash2(words[i]) % CAPACITY;
        if (doubleHashTable2[hash]==NULLSTRING) {
            doubleHashTable2[hash] = words[i];
        } else {
            collisions2++;
            int j=1, tmp;
            while (true) {
                tmp = (hash + j*auxHash(words[i])) % CAPACITY;
                if (doubleHashTable2[tmp]==NULLSTRING) {
                    doubleHashTable2[tmp] = words[i];
                    break;
                }
                collisions2++;
                j++;
            }
        }
    }

    
    cout << "Double Hashing Insertion:\n";
    cout << "\tCollisions by Hash1(): " << collisions1 << "\n";
    cout << "\tCollisions by Hash2(): " << collisions2 << "\n\n";
}

void CustomProbingInsert(string words[], vector<string>&cpTable1, vector<string>&cpTable2) {
    //customHash(k, i) = (Hash(k) + C1 * i * auxHash(k) + C2*i*i) % N
    int c1=271, c2=313;
    int hash, collisions1=0, collisions2=0;

    //Hash1()
    for (int i=0; i<LEN; i++) {
        hash = Hash1(words[i]) % CAPACITY;
        if (cpTable1[hash]==NULLSTRING) {
            cpTable1[hash] = words[i];
        } else {
            collisions1++;
            int j=1, tmp, auxHashValue = auxHash(words[i]);
            while (true) {
                tmp = (hash + c1*j*auxHashValue + c2*j*j) % CAPACITY;
                if (cpTable1[tmp]==NULLSTRING) {
                    cpTable1[tmp] = words[i];
                    break;
                }
                collisions1++;
                j++;
            }
        }
    }

    //Hash2()
    for (int i=0; i<LEN; i++) {
        hash = Hash2(words[i]) % CAPACITY;
        if (cpTable2[hash]==NULLSTRING) {
            cpTable2[hash] = words[i];
        } else {
            collisions2++;
            int j=1, tmp, auxHashValue = auxHash(words[i]);
            while (true) {
                tmp = (hash + c1*j*auxHashValue + c2*j*j) % CAPACITY;
                if (cpTable2[tmp]==NULLSTRING) {
                    cpTable2[tmp] = words[i];
                    break;
                }
                collisions2++;
                j++;
            }
        }
    }

    cout << "Custom Probing Insertion:\n";
    cout << "\tCollisions by Hash1(): " << collisions1 << "\n";
    cout << "\tCollisions by Hash2(): " << collisions2 << "\n\n";

}

//Searching
void SeparateChainingSearch(string words[], vector< vector<string> >&separateChain1, vector< vector<string> >&separateChain2) {
    int probes1[LEN] = {0}, probes2[LEN] = {0};
    int hash, len;
    
    //Hash1()
    for (int i=0; i<LEN; i++) {
        hash = Hash1(words[i]);
        if (separateChain1[hash][0] != NULLSTRING) {
            len = separateChain1[hash].size();
            for (int j=0; j<len; j++) {
                probes1[i]++;
                if (separateChain1[hash][j]==words[i]) {
                    break;
                }
            }
        }
    }

    //Hash2()
    for (int i=0; i<LEN; i++) {
        hash = Hash2(words[i]);
        if (separateChain2[hash][0] != NULLSTRING) {
            len = separateChain2[hash].size();
            for (int j=0; j<len; j++) {
                probes2[i]++;
                if (separateChain2[hash][j]==words[i]) {
                    break;
                }
            }
        }
    }

    double averageProbe1=0.0, averageProbe2=0.0;
    for (int i=0; i<LEN; i++) {
        averageProbe1 += probes1[i]; averageProbe2 += probes2[i];
    }
    averageProbe1 /= LEN; averageProbe2 /= LEN;

    cout << "Separate Chaining Search: \n";
    cout << "\tHash1() average probes: " << averageProbe1 << "\n";
    cout << "\tHash2() average probes: " << averageProbe2 << "\n\n";
}

void DoubleHashingSearch(string words[], vector<string>&doubleHashTable1, vector<string>&doubleHashTable2) {
    int probes1[LEN] = {0}, probes2[LEN] = {0};
    int hash;

    //Hash1()
    for (int i=0; i<LEN; i++) {
        hash = Hash1(words[i]);
        probes1[i]++;

        if (doubleHashTable1[hash] != words[i]) {
            int j=1, tmp, auxHashValue = auxHash(words[i]);
            while (true) {
                tmp = (hash + j*auxHashValue) % CAPACITY;
                probes1[i]++; j++;
                if (doubleHashTable1[tmp] == words[i]) {
                    break;
                }
            }
        }
    }

    //Hash2()
    for (int i=0; i<LEN; i++) {
        hash = Hash2(words[i]);
        probes2[i]++;

        if (doubleHashTable2[hash] != words[i]) {
            int j=1, tmp, auxHashValue = auxHash(words[i]);
            while (true) {
                tmp = (hash + j*auxHashValue) % CAPACITY;
                probes2[i]++; j++;
                if (doubleHashTable2[tmp] == words[i]) {
                    break;
                }
            }
        }
    }

    double averageProbe1=0.0, averageProbe2=0.0;
    for (int i=0; i<LEN; i++) {
        averageProbe1 += probes1[i]; averageProbe2 += probes2[i];
    }
    averageProbe1 /= LEN; averageProbe2 /= LEN;

    cout << "Double Hashing Search: \n";
    cout << "\tHash1() average probes: " << averageProbe1 << "\n";
    cout << "\tHash2() average probes: " << averageProbe2 << "\n\n";
}

void CustomProbingSearch(string words[], vector<string>&cpTable1, vector<string>&cpTable2) {
    int probes1[LEN] = {0}, probes2[LEN] = {0};
    int c1=271, c2=313, hash;

    //Hash1()
    for (int i=0; i<LEN; i++) {
        hash = Hash1(words[i]);
        probes1[i]++;

        if (cpTable1[hash] != words[i]) {
            int j=1, tmp, auxHashValue = auxHash(words[i]);
            while (true) {
                tmp = (hash + c1*j*auxHashValue + c2*j*j) % CAPACITY;
                probes1[i]++; j++;
                if (cpTable1[tmp] == words[i]) {
                    break;
                }
            }
        }
    }

    //Hash2()
    for (int i=0; i<LEN; i++) {
        hash = Hash2(words[i]);
        probes2[i]++;

        if (cpTable2[hash] != words[i]) {
            int j=1, tmp, auxHashValue = auxHash(words[i]);
            while (true) {
                tmp = (hash + c1*j*auxHashValue + c2*j*j) % CAPACITY;
                probes2[i]++; j++;
                if (cpTable2[tmp] == words[i]) {
                    break;
                }
            }
        }
    }

    double averageProbe1=0.0, averageProbe2=0.0;
    for (int i=0; i<LEN; i++) {
        averageProbe1 += probes1[i];
        averageProbe2 += probes2[i];
    }
    averageProbe1 /= LEN;
    averageProbe2 /= LEN;

    cout << "Custom Probing Search: \n";
    cout << "\tHash1() average probes: " << averageProbe1 << "\n";
    cout << "\tHash2() average probes: " << averageProbe2 << "\n\n";
}

//Deletion

void SeparateChainingDelete(string word, vector< vector<string> >&separateChain1, vector< vector<string> >&separateChain2) {
    int hash, len; 
    
    //Hash1()
    hash = Hash1(word); len = separateChain1[hash].size();
    if (len==1) {
        separateChain1[hash].clear();
    } else {
        for (int i=0; i<len; i++) {
            if (separateChain1[hash][i] == word) {
                separateChain1[hash][i] = separateChain1[hash][len-1];
                break;
            }
        }
        separateChain1[hash].pop_back();
    }

    //Hash2()
    hash = Hash2(word); len = separateChain2[hash].size();
    if (len==1) {
        separateChain2[hash].clear();
    } else {
        for (int i=0; i<len; i++) {
            if (separateChain2[hash][i] == word) {
                separateChain2[hash][i] = separateChain2[hash][len-1];
                break;
            }
        }
        separateChain2[hash].pop_back();
    }
}

void DoubleHashingDelete(string word, vector<string>&doubleHashTable1, vector<string>&doubleHashTable2) {
    int hash, len;

    //Hash1()
    hash = Hash1(word);
    if (doubleHashTable1[hash] == word) {
        doubleHashTable1[hash] == NULLSTRING;
    } else {
        int j=1, tmp, auxHashValue = auxHash(word);
        while (true) {
            tmp = (hash + j*auxHashValue) % CAPACITY;
            if (doubleHashTable1[tmp] == word) {
                doubleHashTable1[tmp] = NULLSTRING;
                break;
            }
            j++;
        }
    }

    //Hash2()
    hash = Hash2(word);
    if (doubleHashTable2[hash] == word) {
        doubleHashTable2[hash] == NULLSTRING;
    } else {
        int j=1, tmp, auxHashValue = auxHash(word);
        while (true) {
            tmp = (hash + j*auxHashValue) % CAPACITY;
            if (doubleHashTable2[tmp] == word) {
                doubleHashTable2[tmp] = NULLSTRING;
                break;
            }
            j++;
        }
    }
}

void CustomProbingDelete(string word, vector<string>&cpTable1, vector<string>&cpTable2) {
    int hash, len; 
    
    //Hash1()
    hash = Hash1(word);
    if (cpTable1[hash] == word) {
        cpTable1[hash] == NULLSTRING;
    } else {
        int j=1, tmp, auxHashValue = auxHash(word);
        while (true) {
            tmp = (hash + j*auxHashValue) % CAPACITY;
            if (cpTable1[tmp] == word) {
                cpTable1[tmp] = NULLSTRING;
                break;
            }
            j++;
        }
    }

    //Hash2()
    hash = Hash2(word);
    if (cpTable2[hash] == word) {
        cpTable2[hash] == NULLSTRING;
    } else {
        int j=1, tmp, auxHashValue = auxHash(word);
        while (true) {
            tmp = (hash + j*auxHashValue) % CAPACITY;
            if (cpTable2[tmp] == word) {
                cpTable2[tmp] = NULLSTRING;
                break;
            }
            j++;
        }
    }
} 

//Word Generator
void WordGenerator(string words[], int len) {
    string dictionary[10] = {"lol", "irl", "bro", "wth", "smh", "imo", "ikr", "brb","omg", "mfw"};
    
    for (int a=0; a<0+10; a++) {
        for (int b=0; b<10; b++) {
            for (int c=0; c<10; c++) {
                for (int d=0; d<10; d++) {
                    int i = d+(10*c)+(100*b)+(1000*a);
                    words[i] = "0000000\0";
                    words[i][0] = 'a'+a; 
                    words[i][1] = 'b'+b;
                    words[i][2] = 'c'+c;
                    words[i][3] = 'd'+d; 
                    words[i][4] = dictionary[d][0];
                    words[i][5] = dictionary[d][1];
                    words[i][6] = dictionary[d][2];
                }
            }
        }
    }
}
