#include <bits/stdc++.h>
#include <windows.h>
#include <conio.h>

using namespace std;

map<char, string> Huffman_codes;
map<string, char> canonical_codes;
int arr[500];
void makezero()
{
    for (int i = 0; i < 500; i++)
    {
        arr[i] = 0;
    }
}
int x = 55, y = 30;
int gl = 1;
int ecdsize = 0;
int osize = 0;
void welcome();
void HuffmanCodes(vector<char> data, vector<int> freq, int size);
void get_frequency(string text, vector<char> &ch, vector<int> &freq);
void printCodes(struct MinHeapNode *root, string str);
string encode(string text);
void gotoxy(int x, int y);
void get_canonical_codes();
void printint(vector<int> &freq);
void printch(vector<char> &ch);

void gotoxy(int x, int y)
{
    COORD c;
    c.X = x;
    c.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), c);
}

struct MinHeapNode
{
    char data;
    unsigned freq;
    MinHeapNode *left, *right;
    MinHeapNode(char data, unsigned freq)
    {
        left = right = NULL;
        this -> data = data;
        this -> freq = freq;
    }
};

struct compare
{
    bool operator()(MinHeapNode *l, MinHeapNode *r)
    {
        return (l -> freq > r -> freq);
    }
};

void get_frequency(string text, vector<char> &ch,
                   vector<int> &freq)
{
    for (int j = 0; j < text.size(); j++)
    {
        int num = tolower(text[j]);
        int r = toascii(num);
        arr[r] = arr[r] + 1;
    }
    for (int i = 0; i < text.size(); ++i)
    {
        if (find(ch.begin(), ch.end(), text[i]) == ch.end())
        {
            ch.push_back(text[i]);
            freq.push_back(1);
            continue;
        }
        int index = distance(ch.begin(), find(ch.begin(), ch.end(), text[i]));
        ++freq[index];
    }
    return;
}

void HuffmanCodes(vector<char> data, vector<int> freq, int size)
{
    struct MinHeapNode *left, *right, *top;
    priority_queue<MinHeapNode *, vector<MinHeapNode *>, compare> minHeap;
    for (int i = 0; i < size; ++i)
        minHeap.push(new MinHeapNode(data[i], freq[i]));
    while (minHeap.size() != 1)
    {
        // These two extracted nodes will be the left and right children
        left = minHeap.top();
        minHeap.pop();
        right = minHeap.top();
        minHeap.pop();

        // Create a new internal node with frequency equal to the sum of the
        // two nodes' frequencies
        // Add this node to the min heap
        // '$' is a special value for internal nodes that are not used
        top = new MinHeapNode('$', left -> freq + right -> freq);
        top -> left = left;
        top -> right = right;
        minHeap.push(top);
    }
    printCodes(minHeap.top(), "");
}

string do_padding(unsigned index, unsigned mlength)
{
    string padding;
    if (int((index - 1) / 2) != 0)
    {
        return (int((index - 1) / 2) % 2 == 0) ? (do_padding(int((index - 1) / 2), mlength) + string(mlength + 4, ' ') + " ") : (do_padding(int((index - 1) / 2), mlength) + string(mlength + 3, ' ') + " |");
    }
    return padding;
}

void printer(vector<char> const &tree, unsigned index, unsigned mlength)
{
    auto last = tree.size() - 1;
    auto left = 2 * index + 1;
    auto right = 2 * index + 2;
    cout << " " << tree[index] << " ";
    if (left <= last)
    {
        auto llength = to_string(tree[left]).size();
        cout << "---" << string(mlength - llength, '-');
        printer(tree, left, mlength);
        if (right <= last)
        {
            auto rlength = to_string(tree[right]).size();
            cout << "\n"
                 << do_padding(right, mlength) << string(mlength + 3, ' ') << " | ";
            cout << "\n"
                 << do_padding(right, mlength) << string(mlength + 3, ' ') << " |-" << string(mlength - rlength, '-');
            printer(tree, right, mlength);
        }
    }
}

void print_tree(vector<char> &tree)
{
    unsigned mlength = 0;
    for (char &element : tree)
    {
        auto clength = to_string(element).size();
        if (clength > mlength)
        {
            mlength = to_string(element).size();
        }
    }
    cout << string(mlength - to_string(tree[0]).size(), ' ');
    printer(tree, 0, mlength);
}

void printCodes(struct MinHeapNode *root, string str)
{
    if (!root)
        return;
    if (root -> data != '$')
    {
        int n = tolower(root -> data);
        int rs = toascii(n);
        int pr = arr[rs] * str.size();
        ecdsize = ecdsize + pr;
        osize = osize + arr[rs];
        cout << root -> data << ": " << str << "\n";
        gotoxy(x, y++);
        Huffman_codes[root -> data] = str;
    }
    printCodes(root -> left, str + "0");
    printCodes(root -> right, str + "1");
}

string encode(string text)
{
    int i = 0;
    string encoded_text;
    for (i = 0; i < text.size(); i++)
    {
        encoded_text += Huffman_codes[text[i]];
    }
    return encoded_text;
}

void get_canonical_codes()
{
    char temp;
    string temp_str;
    int i = 0;
    map<char, string>::iterator it = Huffman_codes.begin();
    for (i = 0; i < Huffman_codes.size(); i++)
    {
        temp = it -> first;
        temp_str = it -> second;
        canonical_codes[temp_str] = temp;
        it++;
    }
    return;
}

string get_text(string encoded_text)
{
    int start, length;
    string decoded_text = "";
    start = 0;
    length = 1;
    while (start + length <= encoded_text.size())
    {
        string current = encoded_text.substr(start, length);
        if (canonical_codes.find(current) != canonical_codes.end())
        {
            decoded_text += canonical_codes[current];
            start += length;
            length = 1;
            continue;
        }
        ++length;
    }
    return decoded_text;
}

void delay()
{
    int i = 0, j = 0;
    for (i = 0; i < 10000; i++)
    {
        for (j = 0; j < 1000; j++)
        {
        }
    }
    return;
}

void printch(vector<char> &ch)
{
    cout << endl;
    int i;
    for (i = 0; i < ch.size(); i++)
    {
        cout << ch[i] << " ";
    }
    cout << endl;
    return;
}

void printint(vector<int> &freq)
{
    cout << endl;
    int i;
    for (i = 0; i < freq.size(); i++)
    {
        cout << freq[i] << " ";
    }
    cout << endl;
    return;
}

void welcome()
{
    gotoxy(50, 10);

    cout << "| | ";
    delay();
    cout << "| | ";
    delay();
    cout << ("|= ");
    delay();
    cout << ("|= ");
    delay();
    cout << ("|\\/|   ");
    delay();
    cout << ("/\\   ");
    delay();
    cout << ("|\\  |   ");
    delay();
    cout << (" /  ");
    delay();
    cout << ("_   ");
    delay();
    cout << ("|\\  ");
    delay();
    cout << ("_ _ ");
    delay();
    cout << ("|\\  | ");
    delay();
    cout << (" _   ");
    delay();
    cout << endl;
    gotoxy(50, 11);

    // second line

    cout << ("|_| ");
    delay();
    cout << ("| | ");
    delay();
    cout << ("|= ");
    delay();
    cout << ("|= ");
    delay();
    cout << ("|  |  ");
    delay();
    cout << ("/__\\  ");
    delay();
    cout << ("| \\ |   ");
    delay();
    cout << ("|  ");
    delay();
    cout << ("|\\ | ");
    delay();
    cout << ("| |  ");
    delay();
    cout << ("|  ");
    delay();
    cout << ("| \\ | ");
    delay();
    cout << ("|  _  ");
    delay();
    cout << endl;
    gotoxy(50, 12);

    // third line

    cout << ("| | ");
    delay();
    cout << ("|_| ");
    delay();
    cout << ("|  ");
    delay();
    cout << ("|  ");
    delay();
    cout << ("|  | ");
    delay();
    cout << ("/    \\ ");
    delay();
    cout << ("|  \\|   ");
    delay();
    cout << (" \\ ");
    delay();
    cout << ("|_\\| ");
    delay();
    cout << ("|/  ");
    delay();
    cout << ("_|_ ");
    delay();
    cout << ("|  \\| ");
    delay();
    cout << ("|_| | ");
    delay();
    cout << endl;
    return;
}

int main()
{
    cout << "NOTE:   'input.txt' CONTAINS THE INPUT STRING." << endl;
    cout << "\t'input.txt' AND 'huffman.cpp' MUST BE IN THE SAME DIRECTORY." << endl;
    cout << "\tAN 'encoded.txt' FILE CONTAINING THE ENCODED DATA WILL ALSO BE CREATED IN THE SAME DIRECTORY." << endl;
    cout << "\tA 'output.txt' FILE CONTAINING THE DECODED DATA WILL ALSO BE CREATED IN THE SAME DIRECTORY." << endl;
    system("COLOR 47");
    welcome();
    string line;
    string text;
    ifstream file;
    string filename = "input.txt";
    file.open(filename);
    while (getline(file, line))
    {
        text = text + " " + line;
    }
    file.close();
    cout << endl;
    string encoded_text;
    cout << text << endl;
    vector<char> ch;
    vector<int> freq;
    makezero();
    get_frequency(text, ch, freq);
    cout << "Press Any KEY to print the frequencies of different characters." << endl;
    if (cin.get())
    {
        cout << endl;
        printch(ch);
        printint(freq);
    }

    int size = ch.size();
    cout << "Press Any KEY to print Huffman codes of different characters." << endl;
    if (cin.get())
    {
        cout << endl;
        gotoxy(x, y);
        HuffmanCodes(ch, freq, size);
    }
    gotoxy(0, y);
    print_tree(ch);
   cout<<endl;
    cout << "Press Any KEY to print the encoded and decoded text." << endl;
    if (cin.get())
    {
        encoded_text = encode(text);
        cout << endl;
        cout << "Encoded text: ";
        cout << endl
             << encoded_text << endl;
        ofstream encode("encoded.txt");
        encode << encoded_text;
        encode.close();
    }
    get_canonical_codes();
    string decoded_text;
    cout << endl;
    cout << "Decoded text";
    decoded_text = get_text(encoded_text);
    cout << endl
         << decoded_text << endl;
    int z = osize * 8;
    cout << endl;
    cout << "The size of the original text file is approx. ( assuming each "
            "character "
         << endl;
    cout << "takes 8 bits so total bits = 8 * number of characters) - " << z / 8 << " bytes" << endl;
    cout << endl;
    cout << "The size of the encoding is (assuming each encoded 1/0" << endl;
    cout << "represents 1 bit so total size in bits = size of encoding) - " << ecdsize / 8 << " bytes" << endl;
    cout << endl;
    cout << "Therefore, Huffman coding can be used for compression." << endl;
    ofstream decode("output.txt");
    decode << decoded_text;
    decode.close();
    return 0;
}
