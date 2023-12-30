#include <iostream>
#include <fstream>  // �ļ�����
#include <set>  // ����(set)
#include <map>  // ӳ��(map)
#include <string>
#include <algorithm>
#include <vector>  // ����(vector)
using namespace std;

template <typename T>
class SetManager {
private:
    map<string, set<T>> sets;  // ʹ��map���洢���ϣ����м����ַ�����ֵ������ΪT�ļ���

public:
    // ����һ�����ϣ�����ΪsetName������elements�е�Ԫ��
    void createSet(const string& setName, const set<T>& elements) {
        sets[setName] = elements;  // ��map����ӻ���¾��и������ƺ�Ԫ�صļ���
    }

    // ��ʾ���м��ϵ�����
    void displayAllSets() const {  // auto�ؼ��������Զ������ƶϡ���ʹ��autoʱ�����������Զ����ݳ�ʼ�����ʽ�ƶϱ���������
        for (const auto& pair : sets) {  // ����map�е����м�ֵ��
            cout << pair.first << ": ";  // ��ӡ���ϵ�����
            printSet(pair.second);  // ����printSet������ʾ���ϵ�Ԫ��
            cout << endl;
        }
    }

    // �����м��ϱ��浽�ļ���
    void saveSetsToFile(const string& filename) const {
        ofstream file(filename);  // ����һ������ļ�����ʹ�ø������ļ���
        if (file.is_open()) {
            for (const auto& pair : sets) {
                file << pair.first << ": ";  // �����ϵ�����д���ļ�
                auto it = pair.second.begin();  // ��ȡ���Ͽ�ʼ�ĵ�����
                auto end = pair.second.end();  // ��ȡ���Ͻ����ĵ�����
                while (it != end) {
                    file << *it;  // ����ֱ�����ϵ�ĩβ
                    if (++it != end) {  // ����������һ��Ԫ�أ�����Ԫ�غ���ӿո�
                        file << " ";
                    }
                }
                file << "\n";  // ��ÿ�����Ϻ���ӻ��з�
            }
            file.close();
            cout << "���м����ѱ��浽�ļ� '" << filename << "'" << endl;
        }
        else {
            cout << "�޷����ļ� '" << filename << "' ���б��档" << endl;
        }
    }

    // ���ļ��м��ؼ�������
    void loadSetsFromFile(const string& filename) {
        ifstream file(filename);  // ����һ�������ļ����������ڶ�ȡ�ļ�
        if (file.is_open()) {
            string setName;
            while (file >> setName) {  // ���ļ��ж�ȡ��������
                setName.pop_back();  // �Ƴ���������ĩβ��ð��
                int element;  // ������ʱ�洢�����е�Ԫ��
                set<int> newSet;  // ����һ���µ���������
                while (file >> element) {
                    newSet.insert(element);
                    if (file.peek() == '\n' || file.peek() == EOF)
                        break;  // ����������з����ļ�������������ѭ��
                }
                sets[setName] = newSet;  // ���¼�����ӵ�ӳ����
                file.ignore(numeric_limits<streamsize>::max(), '\n');  // ���Ե�ǰ�е�ʣ�ಿ��
            }
            file.close();
            cout << "���ļ� '" << filename << "' ��ȡ�˼��ϡ�" << endl;
        }
        else {
            cout << "�޷����ļ� '" << filename << "' ���ж�ȡ��" << endl;
        }
    }

    // �����������ϵĽ���  set<T>
    set<T> intersection(const string& setName1, const string& setName2) const {
        set<T> result;  // ����һ���¼������ڴ洢�������
        auto it1 = sets.find(setName1);  // ��ӳ���в��ҵ�һ������
        auto it2 = sets.find(setName2);  // ��ӳ���в��ҵڶ�������
        if (it1 != sets.end() && it2 != sets.end()) {  // ������������Ƿ񶼴���
            set_intersection(it1->second.begin(), it1->second.end(),
                it2->second.begin(), it2->second.end(),
                inserter(result, result.begin()));  // �����������ϵĽ������洢��result��
        }
        else {
            cout << "����ļ���������Ч��" << endl;
        }
        return result;  // ���ؽ������
    }

    // �����������ϵĲ���  set<T>
    set<T> unionSets(const string& setName1, const string& setName2) const {
        set<T> result;
        auto it1 = sets.find(setName1);
        auto it2 = sets.find(setName2);
        if (it1 != sets.end() && it2 != sets.end()) {
            set_union(it1->second.begin(), it1->second.end(),
                it2->second.begin(), it2->second.end(),
                inserter(result, result.begin()));  // �����������ϵĲ������洢��result��
        }
        else {
            cout << "����ļ���������Ч��" << endl;
        }
        return result;  // ���ز������
    }

    // �����������ϵĲ  set<T>
    set<T> difference(const string& setName1, const string& setName2) const {
        set<T> result;
        auto it1 = sets.find(setName1);
        auto it2 = sets.find(setName2);
        if (it1 != sets.end() && it2 != sets.end()) {
            set_difference(it1->second.begin(), it1->second.end(),
                it2->second.begin(), it2->second.end(),
                inserter(result, result.begin()));  // �����������ϵĲ���洢��result��
        }
        else {
            cout << "����ļ���������Ч��" << endl;
        }
        return result;  // ���ز���
    }

    // ���һ�������Ƿ�����һ�����ϵ��Ӽ�  set<T>
    bool isSubset(const string& candidateSetName, const string& mainSetName) const {
        auto it1 = sets.find(candidateSetName);  // ��map�в��Һ�ѡ�Ӽ�
        auto it2 = sets.find(mainSetName);  // ��map�в���������
        if (it1 != sets.end() && it2 != sets.end()) {  // ������������Ƿ񶼴���
            const set<T>& candidateSet = it1->second;  // ��ȡ��ѡ�Ӽ�
            const set<T>& mainSet = it2->second;  // ��ȡ������
            return includes(mainSet.begin(), mainSet.end(),  //includes�ַ���ƥ��
                candidateSet.begin(), candidateSet.end());  // �жϺ�ѡ�Ӽ��Ƿ��������ϵ��Ӽ�
        }
        else {
            cout << "����ļ���������Ч��" << endl;
            return false;
        }
    }

    // �����������ϵĵѿ�����  set<pair<T,T>>�����ڴ洢Ԫ�ضԣ�����ÿ��Ԫ�ض����������ϵ�Ԫ����ɡ�
    set<pair<T, T>> cartesianProduct(const string& setName1, const string& setName2) const {
        set<pair<T, T>> result;  // ����һ���¼������ڴ洢�ѿ��������
        auto it1 = sets.find(setName1);
        auto it2 = sets.find(setName2);
        if (it1 != sets.end() && it2 != sets.end()) {
            for (const T& elem1 : it1->second) {  // ������һ�����ϵ�ÿ��Ԫ��
                for (const T& elem2 : it2->second) {  // �����ڶ������ϵ�ÿ��Ԫ��
                    result.insert(make_pair(elem1, elem2));  // ����Ԫ�ضԵ��������
                }  //make_pair������Ԫ��ı�������ģ��
            }
        }
        else {
            cout << "����ļ���������Ч��" << endl;
        }
        return result;  // ���صѿ��������
    }

    // ��ȡ�ض����ϵĴ�С  set<T>
    int getSetSize(const string& setName) const {
        auto it = sets.find(setName);
        if (it != sets.end()) {
            return it->second.size();  // ���ؼ��ϵĴ�С
        }
        else {
            cout << "����ļ���������Ч��" << endl;
            return -1;
        }
    }

    // ������������Ƿ����  set<T>
    bool areSetsEqual(const string& setName1, const string& setName2) const {
        auto it1 = sets.find(setName1);
        auto it2 = sets.find(setName2);
        if (it1 != sets.end() && it2 != sets.end()) {
            return it1->second == it2->second;  // �Ƚ����������Ƿ����
        }
        else {
            cout << "����ļ���������Ч��" << endl;
            return false;
        }
    }

    // ��ӡ��������
    void printSet(const set<T>& s) const {
        cout << "{ ";
        for (const auto& elem : s) {  // ���������е�ÿ��Ԫ��
            cout << elem << " ";
        }
        cout << "}";
    }

    // ����һ�������������һ�����ϵĲ���  set<T>
    set<T> complement(const string& mainSetName, const string& subSetName) {
        auto itMain = sets.find(mainSetName);  // ��map�в���������
        auto itSub = sets.find(subSetName);  // ��map�в����Ӽ���
        if (itMain != sets.end() && itSub != sets.end()) {
            const set<T>& mainSet = itMain->second;
            const set<T>& subSet = itSub->second;
            set<T> result;  // ����һ���¼������ڴ洢�������
            for (const T& element : mainSet) {  // �����������е�ÿ��Ԫ��
                if (subSet.find(element) == subSet.end()) {  // ���Ԫ�ز����Ӽ�����
                    result.insert(element);  // ��Ԫ����ӵ�������
                }
            }
            return result;  // ���ز������
        }
        else {
            cout << "����ļ���������Ч��" << endl;
            return {};
        }
    }

    // ����һ�����ϵ��ݼ�  set<set<T>>�����ڴ洢���п��ܵ��Ӽ���
    set<set<T>> powerSet(const string& setName) {
        auto it = sets.find(setName);
        if (it != sets.end()) {
            const set<T>& inputSet = it->second;
            set<set<T>> result;  // ����һ���¼������ڴ洢�ݼ����
            vector<T> elements(inputSet.begin(), inputSet.end());  // ������ת��Ϊ����
            int n = elements.size();  // ��ȡ����Ԫ������
            for (int i = 0; i < (1 << n); ++i) {  // ����ÿ�����ܵ����
                set<T> subset;  // ����һ���¼������ڴ洢�Ӽ�
                for (int j = 0; j < n; ++j) {  // ���������е�ÿ��Ԫ��
                    if (i & (1 << j)) {  // ���λ����  ��ʾ������Ԫ�ص�ѡȡ״̬  
                        //ʹ�ö��������ֵ�ÿһλ����������ĳ��λ�õ�Ԫ���Ƿ�ѡȡ  ͨ��λ������Ը�Ч�ر������п��ܵ��Ӽ������
                        subset.insert(elements[j]);  // ��Ԫ����ӵ��Ӽ���
                    }
                }
                result.insert(subset);  // ���Ӽ���ӵ��ݼ���
            }
            return result;  // �����ݼ����
        }
        else {
            cout << "����ļ���������Ч��" << endl;
            return {};
        }
    }

    // ����һ�����ϵ�ȫ����  vector<vector<T>>��������Ϊ��Ҫ�洢���п��ܵ����У�ÿ�����б���Ҳ��һ��˳���б�
    vector<vector<T>> permutations(const string& setName) {
        auto it = sets.find(setName);
        if (it != sets.end()) {
            const set<T>& inputSet = it->second;
            vector<T> elements(inputSet.begin(), inputSet.end());
            vector<vector<T>> result;  // ����һ�����������ڴ洢ȫ���н��
            do {
                result.push_back(elements);  // ����ǰ������ӵ������
            } while (next_permutation(elements.begin(), elements.end()));  // ������һ������  
            //next_permutation��Ϊ������ֵ���������һ���ֵ�������ֵ
            return result;  // ����ȫ���н��
        }
        else {
            cout << "����ļ���������Ч��" << endl;
            return {};
        }
    }

    // ����һ�����ϵ����  vector<vector<T>>�����ڴ洢�ض���С���������
    vector<vector<T>> combinations(const string& setName, int k) {
        auto it = sets.find(setName);
        if (it != sets.end()) {
            const set<T>& inputSet = it->second;
            vector<T> elements(inputSet.begin(), inputSet.end());
            vector<vector<T>> result;  // ����һ�����������ڴ洢��Ͻ��
            int n = elements.size();  // ��ȡ����Ԫ������
            vector<bool> bitmask(n, false);  // ����һ��λ����
            fill(bitmask.begin(), bitmask.begin() + k, true);  // ��ʼ��λ����  ��ʾ������Ԫ�ص�ѡȡ״̬
            do {
                vector<T> combination;  // ����һ�����������ڴ洢��ǰ���
                for (int i = 0; i < n; ++i) {
                    if (bitmask[i]) {  // ���λ����Ϊtrue
                        combination.push_back(elements[i]);  // ��Ԫ����ӵ���ǰ�����
                    }
                }
                result.push_back(combination);  // ����ǰ�����ӵ������
            } while (prev_permutation(bitmask.begin(), bitmask.end()));  // ������һ�����
            //prev_permutation��Ϊ����ֵ���������ǰ���ֵ���Ž�С��ֵ
            return result;  // ������Ͻ��
        }
        else {
            cout << "����ļ���������Ч��" << endl;
            return {};
        }
    }
};

/*map���ڽ����������������ݣ�set<T>����������set���ڴ洢���ظ���Ԫ�ء�
������Ҫ���к���ϵĲ�����ʹ��vector���洢��ʱ�������Ϊvector�����ظ�Ԫ�ز��ҿ������ɵؽ���˳����ʺ͵�����*/

int main() {
    SetManager<int> setManager;  // ����һ���������͵�SetManager����

    while (true) {
        cout << "---------------------------------------------------------" << endl;
        cout << "|      a.  �����¼���                                   |" << endl;
        cout << "|      b.  ��ʾ���м���                                 |" << endl;
        cout << "|      c.  ���漯�ϵ��ļ�                               |" << endl;
        cout << "|      d.  ���ļ���ȡ����                               |" << endl;
        cout << "|      e.  ���㼯�ϵĽ���                               |" << endl;
        cout << "|      f.  ���㼯�ϵĲ���                               |" << endl;
        cout << "|      g.  ���㼯�ϵĲ                               |" << endl;
        cout << "|      h.  ��鼯�ϵ��Ӽ�                               |" << endl;
        cout << "|      i.  ���㼯�ϵĵѿ�����                           |" << endl;
        cout << "|      j.  ���㼯�ϵĴ�С                               |" << endl;
        cout << "|      k.  ���㼯�ϵĲ���                               |" << endl;
        cout << "|      l.  ���㼯�ϵ��ݼ�                               |" << endl;
        cout << "|      m.  ���㼯�ϵ�����                               |" << endl;
        cout << "|      n.  ���㼯�ϵ����                               |" << endl;
        cout << "|      o.  ������������Ƿ����                         |" << endl;
        cout << "|      p.  �˳�����ϵͳ                                 |" << endl;
        cout << "---------------------------------------------------------" << endl;
        cout << "���������ţ�";

        char choice;
        cin >> choice;

        switch (choice) {
        case 'a': {
            string setName;
            cout << "�����¼��ϵ�����: ";
            cin >> setName;

            set<int> newSet;
            int element;
            cout << "�����¼��ϵ�Ԫ�أ��������Կո�ָ���: ";
            while (cin >> element) {
                newSet.insert(element);
                if (cin.get() == '\n') break;
            }
            setManager.createSet(setName, newSet);
            break;
        }
        case 'b':
            setManager.displayAllSets();
            break;
        case 'c': {
            string filename;
            cout << "����Ҫ������ļ���: ";
            cin >> filename;
            setManager.saveSetsToFile(filename);
            break;
        }
        case 'd': {
            string filename;
            cout << "����Ҫ��ȡ���ļ���: ";
            cin >> filename;
            setManager.loadSetsFromFile(filename);
            break;
        }
        case 'e': {
            string setName1, setName2;
            cout << "�����һ�����ϵ�����: ";
            cin >> setName1;
            cout << "����ڶ������ϵ�����: ";
            cin >> setName2;
            set<int> intersection = setManager.intersection(setName1, setName2);
            cout << "����: ";
            setManager.printSet(intersection);
            cout << endl;
            break;
        }
        case 'f': {
            string setName1, setName2;
            cout << "�����һ�����ϵ�����: ";
            cin >> setName1;
            cout << "����ڶ������ϵ�����: ";
            cin >> setName2;
            set<int> unionSet = setManager.unionSets(setName1, setName2);
            cout << "����: ";
            setManager.printSet(unionSet);
            cout << endl;
            break;
        }
        case 'g': {
            string setName1, setName2;
            cout << "�����һ�����ϵ�����: ";
            cin >> setName1;
            cout << "����ڶ������ϵ�����: ";
            cin >> setName2;
            set<int> difference = setManager.difference(setName1, setName2);
            cout << "�: ";
            setManager.printSet(difference);
            cout << endl;
            break;
        }
        case 'h': {
            string candidateSetName, mainSetName;
            cout << "�����ѡ�Ӽ�������: ";
            cin >> candidateSetName;
            cout << "���븸��������: ";
            cin >> mainSetName;
            if (setManager.isSubset(candidateSetName, mainSetName)) {
                cout << "'" << candidateSetName << "' �� '" << mainSetName << "' ���Ӽ���" << endl;
            }
            else {
                cout << "'" << candidateSetName << "' ���� '" << mainSetName << "' ���Ӽ���" << endl;
            }
            break;
        }
        case 'i': {
            string setName1, setName2;
            cout << "�����һ�����ϵ�����: ";
            cin >> setName1;
            cout << "����ڶ������ϵ�����: ";
            cin >> setName2;
            set<pair<int, int>> cartesian = setManager.cartesianProduct(setName1, setName2);
            cout << "�ѿ�����: { ";
            for (const auto& elem : cartesian) {
                cout << "(" << elem.first << ", " << elem.second << ") ";
            }
            cout << "}" << endl;
            break;
        }
        case 'j': {
            string setName;
            cout << "���뼯�ϵ�����: ";
            cin >> setName;
            int setSize = setManager.getSetSize(setName);
            if (setSize != -1) {
                cout << "���� '" << setName << "' �Ĵ�СΪ: " << setSize << endl;
            }
            break;
        }
        case 'k': {
            string setName1, setName2;
            cout << "���������ϵ�����: ";
            cin >> setName1;
            cout << "�����Ӽ��ϵ�����: ";
            cin >> setName2;
            set<int> complementSet = setManager.complement(setName1, setName2);
            cout << "����: ";
            setManager.printSet(complementSet);
            cout << endl;
            break;
        }
        case 'l': {
            string setName;
            cout << "���뼯�ϵ�����: ";
            cin >> setName;
            set<set<int>> powerSet = setManager.powerSet(setName);
            cout << "�ݼ�: " << endl;
            for (const auto& subset : powerSet) {
                setManager.printSet(subset);
                cout << endl;
            }
            break;
        }
        case 'm': {
            string setName;
            cout << "���뼯�ϵ�����: ";
            cin >> setName;
            vector<vector<int>> perms = setManager.permutations(setName);
            cout << "����: " << endl;
            for (const auto& perm : perms) {
                for (const int& element : perm) {
                    cout << element << " ";
                }
                cout << endl;
            }
            break;
        }
        case 'n': {
            string setName;
            cout << "���뼯�ϵ�����: ";
            cin >> setName;
            int k;
            cout << "������ϴ�С (k): ";
            cin >> k;
            vector<vector<int>> combos = setManager.combinations(setName, k);
            cout << "���: " << endl;
            for (const auto& combo : combos) {
                for (const int& element : combo) {
                    cout << element << " ";
                }
                cout << endl;
            }
            break;
        }
        case 'o': {
            string setName1, setName2;
            cout << "�����һ�����ϵ�����: ";
            cin >> setName1;
            cout << "����ڶ������ϵ�����: ";
            cin >> setName2;
            bool areEqual = setManager.areSetsEqual(setName1, setName2);
            if (areEqual) {
                cout << "���� '" << setName1 << "' �� '" << setName2 << "' ��ȡ�" << endl;
            }
            else {
                cout << "���� '" << setName1 << "' �� '" << setName2 << "' ����ȡ�" << endl;
            }
            break;
        }
        case 'p':
            cout << "ллʹ�ã�" << endl;
            return 0;
        default:
            cout << "��Ч��ѡ��������ѡ��" << endl;
        }
    }

    return 0;
}