#include <iostream>
#include <fstream>  // 文件操作
#include <set>  // 集合(set)
#include <map>  // 映射(map)
#include <string>
#include <algorithm>
#include <vector>  // 向量(vector)
using namespace std;

template <typename T>
class SetManager {
private:
    map<string, set<T>> sets;  // 使用map来存储集合，其中键是字符串，值是类型为T的集合

public:
    // 创建一个集合，名称为setName，包含elements中的元素
    void createSet(const string& setName, const set<T>& elements) {
        sets[setName] = elements;  // 在map中添加或更新具有给定名称和元素的集合
    }

    // 显示所有集合的内容
    void displayAllSets() const {  // auto关键字用于自动类型推断。当使用auto时，编译器会自动根据初始化表达式推断变量的类型
        for (const auto& pair : sets) {  // 遍历map中的所有键值对
            cout << pair.first << ": ";  // 打印集合的名称
            printSet(pair.second);  // 调用printSet函数显示集合的元素
            cout << endl;
        }
    }

    // 将所有集合保存到文件中
    void saveSetsToFile(const string& filename) const {
        ofstream file(filename);  // 创建一个输出文件流，使用给定的文件名
        if (file.is_open()) {
            for (const auto& pair : sets) {
                file << pair.first << ": ";  // 将集合的名称写入文件
                auto it = pair.second.begin();  // 获取集合开始的迭代器
                auto end = pair.second.end();  // 获取集合结束的迭代器
                while (it != end) {
                    file << *it;  // 遍历直到集合的末尾
                    if (++it != end) {  // 如果不是最后一个元素，则在元素后添加空格
                        file << " ";
                    }
                }
                file << "\n";  // 在每个集合后添加换行符
            }
            file.close();
            cout << "所有集合已保存到文件 '" << filename << "'" << endl;
        }
        else {
            cout << "无法打开文件 '" << filename << "' 进行保存。" << endl;
        }
    }

    // 从文件中加载集合数据
    void loadSetsFromFile(const string& filename) {
        ifstream file(filename);  // 创建一个输入文件流对象，用于读取文件
        if (file.is_open()) {
            string setName;
            while (file >> setName) {  // 从文件中读取集合名称
                setName.pop_back();  // 移除集合名称末尾的冒号
                int element;  // 用于临时存储集合中的元素
                set<int> newSet;  // 创建一个新的整数集合
                while (file >> element) {
                    newSet.insert(element);
                    if (file.peek() == '\n' || file.peek() == EOF)
                        break;  // 如果遇到换行符或文件结束符，跳出循环
                }
                sets[setName] = newSet;  // 将新集合添加到映射中
                file.ignore(numeric_limits<streamsize>::max(), '\n');  // 忽略当前行的剩余部分
            }
            file.close();
            cout << "从文件 '" << filename << "' 读取了集合。" << endl;
        }
        else {
            cout << "无法打开文件 '" << filename << "' 进行读取。" << endl;
        }
    }

    // 计算两个集合的交集  set<T>
    set<T> intersection(const string& setName1, const string& setName2) const {
        set<T> result;  // 创建一个新集合用于存储交集结果
        auto it1 = sets.find(setName1);  // 在映射中查找第一个集合
        auto it2 = sets.find(setName2);  // 在映射中查找第二个集合
        if (it1 != sets.end() && it2 != sets.end()) {  // 检查两个集合是否都存在
            set_intersection(it1->second.begin(), it1->second.end(),
                it2->second.begin(), it2->second.end(),
                inserter(result, result.begin()));  // 计算两个集合的交集并存储在result中
        }
        else {
            cout << "输入的集合名称无效。" << endl;
        }
        return result;  // 返回交集结果
    }

    // 计算两个集合的并集  set<T>
    set<T> unionSets(const string& setName1, const string& setName2) const {
        set<T> result;
        auto it1 = sets.find(setName1);
        auto it2 = sets.find(setName2);
        if (it1 != sets.end() && it2 != sets.end()) {
            set_union(it1->second.begin(), it1->second.end(),
                it2->second.begin(), it2->second.end(),
                inserter(result, result.begin()));  // 计算两个集合的并集并存储在result中
        }
        else {
            cout << "输入的集合名称无效。" << endl;
        }
        return result;  // 返回并集结果
    }

    // 计算两个集合的差集  set<T>
    set<T> difference(const string& setName1, const string& setName2) const {
        set<T> result;
        auto it1 = sets.find(setName1);
        auto it2 = sets.find(setName2);
        if (it1 != sets.end() && it2 != sets.end()) {
            set_difference(it1->second.begin(), it1->second.end(),
                it2->second.begin(), it2->second.end(),
                inserter(result, result.begin()));  // 计算两个集合的差集并存储在result中
        }
        else {
            cout << "输入的集合名称无效。" << endl;
        }
        return result;  // 返回差集结果
    }

    // 检查一个集合是否是另一个集合的子集  set<T>
    bool isSubset(const string& candidateSetName, const string& mainSetName) const {
        auto it1 = sets.find(candidateSetName);  // 在map中查找候选子集
        auto it2 = sets.find(mainSetName);  // 在map中查找主集合
        if (it1 != sets.end() && it2 != sets.end()) {  // 检查两个集合是否都存在
            const set<T>& candidateSet = it1->second;  // 获取候选子集
            const set<T>& mainSet = it2->second;  // 获取主集合
            return includes(mainSet.begin(), mainSet.end(),  //includes字符串匹配
                candidateSet.begin(), candidateSet.end());  // 判断候选子集是否是主集合的子集
        }
        else {
            cout << "输入的集合名称无效。" << endl;
            return false;
        }
    }

    // 计算两个集合的笛卡尔积  set<pair<T,T>>，用于存储元素对，其中每个元素对由两个集合的元素组成。
    set<pair<T, T>> cartesianProduct(const string& setName1, const string& setName2) const {
        set<pair<T, T>> result;  // 创建一个新集合用于存储笛卡尔积结果
        auto it1 = sets.find(setName1);
        auto it2 = sets.find(setName2);
        if (it1 != sets.end() && it2 != sets.end()) {
            for (const T& elem1 : it1->second) {  // 遍历第一个集合的每个元素
                for (const T& elem2 : it2->second) {  // 遍历第二个集合的每个元素
                    result.insert(make_pair(elem1, elem2));  // 插入元素对到结果集合
                }  //make_pair创建二元组的便利函数模板
            }
        }
        else {
            cout << "输入的集合名称无效。" << endl;
        }
        return result;  // 返回笛卡尔积结果
    }

    // 获取特定集合的大小  set<T>
    int getSetSize(const string& setName) const {
        auto it = sets.find(setName);
        if (it != sets.end()) {
            return it->second.size();  // 返回集合的大小
        }
        else {
            cout << "输入的集合名称无效。" << endl;
            return -1;
        }
    }

    // 检查两个集合是否相等  set<T>
    bool areSetsEqual(const string& setName1, const string& setName2) const {
        auto it1 = sets.find(setName1);
        auto it2 = sets.find(setName2);
        if (it1 != sets.end() && it2 != sets.end()) {
            return it1->second == it2->second;  // 比较两个集合是否相等
        }
        else {
            cout << "输入的集合名称无效。" << endl;
            return false;
        }
    }

    // 打印集合内容
    void printSet(const set<T>& s) const {
        cout << "{ ";
        for (const auto& elem : s) {  // 遍历集合中的每个元素
            cout << elem << " ";
        }
        cout << "}";
    }

    // 计算一个集合相对于另一个集合的补集  set<T>
    set<T> complement(const string& mainSetName, const string& subSetName) {
        auto itMain = sets.find(mainSetName);  // 在map中查找主集合
        auto itSub = sets.find(subSetName);  // 在map中查找子集合
        if (itMain != sets.end() && itSub != sets.end()) {
            const set<T>& mainSet = itMain->second;
            const set<T>& subSet = itSub->second;
            set<T> result;  // 创建一个新集合用于存储补集结果
            for (const T& element : mainSet) {  // 遍历主集合中的每个元素
                if (subSet.find(element) == subSet.end()) {  // 如果元素不在子集合中
                    result.insert(element);  // 将元素添加到补集中
                }
            }
            return result;  // 返回补集结果
        }
        else {
            cout << "输入的集合名称无效。" << endl;
            return {};
        }
    }

    // 计算一个集合的幂集  set<set<T>>，用于存储所有可能的子集合
    set<set<T>> powerSet(const string& setName) {
        auto it = sets.find(setName);
        if (it != sets.end()) {
            const set<T>& inputSet = it->second;
            set<set<T>> result;  // 创建一个新集合用于存储幂集结果
            vector<T> elements(inputSet.begin(), inputSet.end());  // 将集合转换为向量
            int n = elements.size();  // 获取集合元素数量
            for (int i = 0; i < (1 << n); ++i) {  // 对于每个可能的组合
                set<T> subset;  // 创建一个新集合用于存储子集
                for (int j = 0; j < n; ++j) {  // 遍历集合中的每个元素
                    if (i & (1 << j)) {  // 检查位掩码  表示集合中元素的选取状态  
                        //使用二进制数字的每一位来代表集合中某个位置的元素是否被选取  通过位运算可以高效地遍历所有可能的子集或组合
                        subset.insert(elements[j]);  // 将元素添加到子集中
                    }
                }
                result.insert(subset);  // 将子集添加到幂集中
            }
            return result;  // 返回幂集结果
        }
        else {
            cout << "输入的集合名称无效。" << endl;
            return {};
        }
    }

    // 计算一个集合的全排列  vector<vector<T>>，这是因为需要存储所有可能的排列，每个排列本身也是一个顺序列表
    vector<vector<T>> permutations(const string& setName) {
        auto it = sets.find(setName);
        if (it != sets.end()) {
            const set<T>& inputSet = it->second;
            vector<T> elements(inputSet.begin(), inputSet.end());
            vector<vector<T>> result;  // 创建一个新向量用于存储全排列结果
            do {
                result.push_back(elements);  // 将当前排列添加到结果中
            } while (next_permutation(elements.begin(), elements.end()));  // 生成下一个排列  
            //next_permutation是为给定的值数组查找下一个字典序更大的值
            return result;  // 返回全排列结果
        }
        else {
            cout << "输入的集合名称无效。" << endl;
            return {};
        }
    }

    // 计算一个集合的组合  vector<vector<T>>，用于存储特定大小的所有组合
    vector<vector<T>> combinations(const string& setName, int k) {
        auto it = sets.find(setName);
        if (it != sets.end()) {
            const set<T>& inputSet = it->second;
            vector<T> elements(inputSet.begin(), inputSet.end());
            vector<vector<T>> result;  // 创建一个新向量用于存储组合结果
            int n = elements.size();  // 获取集合元素数量
            vector<bool> bitmask(n, false);  // 创建一个位掩码
            fill(bitmask.begin(), bitmask.begin() + k, true);  // 初始化位掩码  表示集合中元素的选取状态
            do {
                vector<T> combination;  // 创建一个新向量用于存储当前组合
                for (int i = 0; i < n; ++i) {
                    if (bitmask[i]) {  // 如果位掩码为true
                        combination.push_back(elements[i]);  // 将元素添加到当前组合中
                    }
                }
                result.push_back(combination);  // 将当前组合添加到结果中
            } while (prev_permutation(bitmask.begin(), bitmask.end()));  // 生成下一个组合
            //prev_permutation是为给定值数组查找先前的字典编排较小的值
            return result;  // 返回组合结果
        }
        else {
            cout << "输入的集合名称无效。" << endl;
            return {};
        }
    }
};

/*map用于将集合名称与其内容（set<T>）关联，而set用于存储不重复的元素。
对于需要排列和组合的操作，使用vector来存储临时结果，因为vector允许重复元素并且可以轻松地进行顺序访问和迭代。*/

int main() {
    SetManager<int> setManager;  // 创建一个整数类型的SetManager对象

    while (true) {
        cout << "---------------------------------------------------------" << endl;
        cout << "|      a.  创建新集合                                   |" << endl;
        cout << "|      b.  显示所有集合                                 |" << endl;
        cout << "|      c.  保存集合到文件                               |" << endl;
        cout << "|      d.  从文件读取集合                               |" << endl;
        cout << "|      e.  计算集合的交集                               |" << endl;
        cout << "|      f.  计算集合的并集                               |" << endl;
        cout << "|      g.  计算集合的差集                               |" << endl;
        cout << "|      h.  检查集合的子集                               |" << endl;
        cout << "|      i.  计算集合的笛卡尔积                           |" << endl;
        cout << "|      j.  计算集合的大小                               |" << endl;
        cout << "|      k.  计算集合的补集                               |" << endl;
        cout << "|      l.  计算集合的幂集                               |" << endl;
        cout << "|      m.  计算集合的排列                               |" << endl;
        cout << "|      n.  计算集合的组合                               |" << endl;
        cout << "|      o.  检查两个集合是否相等                         |" << endl;
        cout << "|      p.  退出集合系统                                 |" << endl;
        cout << "---------------------------------------------------------" << endl;
        cout << "输入操作编号：";

        char choice;
        cin >> choice;

        switch (choice) {
        case 'a': {
            string setName;
            cout << "输入新集合的名称: ";
            cin >> setName;

            set<int> newSet;
            int element;
            cout << "输入新集合的元素（整数，以空格分隔）: ";
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
            cout << "输入要保存的文件名: ";
            cin >> filename;
            setManager.saveSetsToFile(filename);
            break;
        }
        case 'd': {
            string filename;
            cout << "输入要读取的文件名: ";
            cin >> filename;
            setManager.loadSetsFromFile(filename);
            break;
        }
        case 'e': {
            string setName1, setName2;
            cout << "输入第一个集合的名称: ";
            cin >> setName1;
            cout << "输入第二个集合的名称: ";
            cin >> setName2;
            set<int> intersection = setManager.intersection(setName1, setName2);
            cout << "交集: ";
            setManager.printSet(intersection);
            cout << endl;
            break;
        }
        case 'f': {
            string setName1, setName2;
            cout << "输入第一个集合的名称: ";
            cin >> setName1;
            cout << "输入第二个集合的名称: ";
            cin >> setName2;
            set<int> unionSet = setManager.unionSets(setName1, setName2);
            cout << "并集: ";
            setManager.printSet(unionSet);
            cout << endl;
            break;
        }
        case 'g': {
            string setName1, setName2;
            cout << "输入第一个集合的名称: ";
            cin >> setName1;
            cout << "输入第二个集合的名称: ";
            cin >> setName2;
            set<int> difference = setManager.difference(setName1, setName2);
            cout << "差集: ";
            setManager.printSet(difference);
            cout << endl;
            break;
        }
        case 'h': {
            string candidateSetName, mainSetName;
            cout << "输入候选子集的名称: ";
            cin >> candidateSetName;
            cout << "输入父集的名称: ";
            cin >> mainSetName;
            if (setManager.isSubset(candidateSetName, mainSetName)) {
                cout << "'" << candidateSetName << "' 是 '" << mainSetName << "' 的子集。" << endl;
            }
            else {
                cout << "'" << candidateSetName << "' 不是 '" << mainSetName << "' 的子集。" << endl;
            }
            break;
        }
        case 'i': {
            string setName1, setName2;
            cout << "输入第一个集合的名称: ";
            cin >> setName1;
            cout << "输入第二个集合的名称: ";
            cin >> setName2;
            set<pair<int, int>> cartesian = setManager.cartesianProduct(setName1, setName2);
            cout << "笛卡尔积: { ";
            for (const auto& elem : cartesian) {
                cout << "(" << elem.first << ", " << elem.second << ") ";
            }
            cout << "}" << endl;
            break;
        }
        case 'j': {
            string setName;
            cout << "输入集合的名称: ";
            cin >> setName;
            int setSize = setManager.getSetSize(setName);
            if (setSize != -1) {
                cout << "集合 '" << setName << "' 的大小为: " << setSize << endl;
            }
            break;
        }
        case 'k': {
            string setName1, setName2;
            cout << "输入主集合的名称: ";
            cin >> setName1;
            cout << "输入子集合的名称: ";
            cin >> setName2;
            set<int> complementSet = setManager.complement(setName1, setName2);
            cout << "补集: ";
            setManager.printSet(complementSet);
            cout << endl;
            break;
        }
        case 'l': {
            string setName;
            cout << "输入集合的名称: ";
            cin >> setName;
            set<set<int>> powerSet = setManager.powerSet(setName);
            cout << "幂集: " << endl;
            for (const auto& subset : powerSet) {
                setManager.printSet(subset);
                cout << endl;
            }
            break;
        }
        case 'm': {
            string setName;
            cout << "输入集合的名称: ";
            cin >> setName;
            vector<vector<int>> perms = setManager.permutations(setName);
            cout << "排列: " << endl;
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
            cout << "输入集合的名称: ";
            cin >> setName;
            int k;
            cout << "输入组合大小 (k): ";
            cin >> k;
            vector<vector<int>> combos = setManager.combinations(setName, k);
            cout << "组合: " << endl;
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
            cout << "输入第一个集合的名称: ";
            cin >> setName1;
            cout << "输入第二个集合的名称: ";
            cin >> setName2;
            bool areEqual = setManager.areSetsEqual(setName1, setName2);
            if (areEqual) {
                cout << "集合 '" << setName1 << "' 和 '" << setName2 << "' 相等。" << endl;
            }
            else {
                cout << "集合 '" << setName1 << "' 和 '" << setName2 << "' 不相等。" << endl;
            }
            break;
        }
        case 'p':
            cout << "谢谢使用！" << endl;
            return 0;
        default:
            cout << "无效的选择，请重新选择。" << endl;
        }
    }

    return 0;
}