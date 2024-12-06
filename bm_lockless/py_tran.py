import sys
import pandas as pd


def extract_to_excel(input_file):
    data = []  # 初始化数据列表，用于收集每行解析后的数据
    with open(input_file, 'r') as f:
        for line in f:
            line = line.strip()
            if not line or line.startswith('#'):
                continue  # 跳过空行和注释行
            # 对特定行进行处理，去除不需要的部分
            if line.startswith('Requires'):
                line = line.split(':')[1].strip()  # 只保留冒号后面的部分
            # 假设每行的内容现在可以按照空格分成列
            columns = line.split()  # 按空格分割每行的内容
            data.append(columns)  # 将处理后的列数据添加到列表中
        
        #文本数字转成数字
        for i in range(len(data)):
            for j in range(len(data[i])):
                if data[i][j].isdigit():
                    data[i][j] = int(data[i][j])


    # 使用Pandas创建DataFrame
    df = pd.DataFrame(data)
    # 保存DataFrame到Excel文件，假设每个列表项是一行数据
    df.to_excel('output.xlsx', index=False, header=False)  # 不包含行索引和列标题

if __name__ == '__main__':
    if len(sys.argv) < 2:
        print("请提供输入文件路径。")
        sys.exit(1)
    input_file = sys.argv[1]
    extract_to_excel(input_file)