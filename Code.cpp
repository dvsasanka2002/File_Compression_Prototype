#include <bits/stdc++.h>
 
using namespace std;
class HuffmanCoding{
    public:
    //Defining the node of a tree and its structure
    struct TreeNode {
    char ch;
    int freq;
    TreeNode *left, *right;
    TreeNode(char ch, int freq){
        this->ch = ch;
        this->freq = freq;
        left = right = NULL;
    }
};
 
//Comparator struct to be used by Priority queue later
struct compareNodes {
    bool operator()(TreeNode* node1, TreeNode* node2){
        return (node1->freq > node2->freq);
    }
};
 
//Instance variables 
map<char,string> encoding;   //Stores the encoded string of every character in the text
priority_queue<TreeNode*, vector<TreeNode*>, compareNodes> MinHeap;   //Minheap for all leaf nodes
 
//To generates a map of frequencies of unique characters 
map<char, int> getFreqMap(string txt){ 
    map<char, int> hm;
    for(auto &i: txt){
        if (hm.find(i) == hm.end()){
            hm.insert({i, 1});
        }
        else{
            hm.at(i) += 1;
        }
    }
    return hm;
}
 
//To build the Huffman Tree
TreeNode* buildTree(map<char, int> hm){
    // declartion of temporary tree node variables
    struct TreeNode *left, *right, *head;
    // inserts all the unique characters into the priority_queue
    for(auto& i: hm){
        MinHeap.push(new TreeNode(i.first, i.second));
    }
    //building the tree
    while (MinHeap.size() != 1) {
        left = MinHeap.top();
        MinHeap.pop();
  
        right = MinHeap.top();
        MinHeap.pop();
  
        //Create a node having sum of the frequencies of its children as its frequency
        head = new TreeNode('$', left->freq + right->freq);
  
        head->left = left;
        head->right = right;
        
        MinHeap.push(head);
    }
    // return root of the built tree
    return MinHeap.top();
}
 
//To generate the encoded string of every character 
void getEncodingMap(struct TreeNode* root, string code){
    if (!root){
        return;
    }
    //Store the code of the character in the leaf node that we hit while traversing
    if (root->ch != '$'){
        encoding.insert({root->ch, code});
    }
    getEncodingMap(root->left, code + "0");   //When traversing to the left child, add '0' to the code
    getEncodingMap(root->right, code + "1");  //When traversing to the left child, add '1' to the code
}
 
//To generate the encoded string for the input text
string encode(string txt, map<char ,string> encoding){
    string encodedText = "";
    for(auto i: txt){
        encodedText += encoding.at(i);
    }
    return encodedText;
}
 
//To decode the generated encoded string
string decode(struct TreeNode* root, string bits){
    if(root->left == NULL && root->right == NULL){
        char letter = root->ch;
        string output = "";
        for (int i = 0; i < bits.length(); i++) {
            output += letter;
        }
        return output;
        
    }
    string output = "";
    struct TreeNode* temp = root;
    //Traverse the tree until a leaf node is encountered
    for (auto i: bits){
        if (i == '0'){
            temp = temp->left;
        }
        else{
            temp = temp->right;
        }
        //Append the character of the leaf node encountered to the output
        if (temp->left == NULL and temp->right == NULL){
            output += temp->ch;
            temp = root;
        }
    }
    return output;
}
void printOutput(string txt){
    map<char, int> freqMap = getFreqMap(txt);
    string bitString;
    TreeNode* tree = buildTree(freqMap);
    if(freqMap.size() == 1){
        char letter = txt[0];
        string code = "0";
        encoding.insert({letter,code});
        for (int i = 0; i < txt.length(); i++) {
            bitString += "0";
        }
    }
    else{
        getEncodingMap(tree,"");
        bitString = encode(txt, encoding);
    }
    for (auto i: encoding){
        cout << i.first << ": " << i.second << endl;
    }  
    cout << bitString << endl;
    string data = decode(tree, bitString);
    cout << "Decoded Message: "<< data << endl;
}
};
    
int main()
{
    HuffmanCoding hc;
    hc.printOutput("BBBB CCCAAR");
}