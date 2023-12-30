# SetManager - 集合管理系统

## 简介
SetManager 是一个基于 C++ 的集合管理系统，提供了创建、操作和存储集合的功能。此系统支持集合的基本运算，如交集、并集、差集，以及更高级的功能，如笛卡尔积、幂集、排列和组合等。

## 功能
- **创建新集合**: 创建包含特定元素的新集合。
- **显示所有集合**: 显示当前所有创建的集合及其内容。
- **保存集合到文件**: 将当前所有集合保存到指定的文件中。
- **从文件读取集合**: 从指定文件中读取集合信息。
- **集合的交集、并集和差集**: 计算两个集合的交集、并集和差集。
- **检查集合的子集**: 判断一个集合是否是另一个集合的子集。
- **集合的笛卡尔积**: 计算两个集合的笛卡尔积。
- **计算集合的大小**: 获取特定集合的元素数量。
- **计算集合的补集**: 计算一个集合相对于另一个集合的补集。
- **计算集合的幂集**: 生成一个集合的所有子集构成的集合（幂集）。
- **计算集合的排列**: 生成集合元素的所有排列。
- **计算集合的组合**: 生成集合中特定数量元素的所有组合。
- **检查两个集合是否相等**: 判断两个集合是否包含相同的元素。

## 使用指南
1. **创建集合**: 使用 `createSet` 方法，输入集合名称和元素。
2. **显示集合**: 使用 `displayAllSets` 方法查看所有集合。
3. **文件操作**: 使用 `saveSetsToFile` 和 `loadSetsFromFile` 方法进行集合的保存和加载。
4. **集合运算**: 使用相应的方法进行交集、并集、差集等运算。
5. **子集和笛卡尔积**: 使用 `isSubset` 和 `cartesianProduct` 方法。
6. **集合属性**: 使用 `getSetSize`、`complement`、`powerSet`、`permutations` 和 `combinations` 方法查询集合属性和生成新集合。

## 退出系统
使用命令 `'p'` 可以退出集合管理系统。

## 开发者信息
- **语言**: C++
- **环境**: 任何支持 C++ 的编程环境

## 注意事项
- 输入时请按照程序提示正确输入。
- 文件操作时，请确保文件路径正确无误。
- 在进行集合操作时，请确保所需集合已经创建。
