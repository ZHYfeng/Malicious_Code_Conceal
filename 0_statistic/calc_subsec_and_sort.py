# coding=utf8

import argparse
import os
import json
import itertools

RANKING_FILE = os.path.abspath(os.path.join(os.path.dirname(__file__), "ranking_func.log"))
RESULT_FILE = os.path.abspath(os.path.join(os.path.dirname(__file__), 'statistics.log'))


def read_ranking_file(file):
    with open(file, "r") as f:
        ranking_funcs = json.load(f)
    return ranking_funcs


def parse_line(line):
    line.strip()
    line = line.replace("\n", "")
    line = line.replace(" ", "")
    funcs = line.split(",")
    return funcs


class SubsequenceProcessor:
    """
    calcuate the occurrence of each subsequence and sort it 
    """
    @staticmethod
    def get_key(func_list):
        return '-'.join(func_list)

    def __init__(self, target, trace_file):
        self.__target = target
        self.__trace_file = trace_file
        self.__result = dict()
        self.__result_file = ''.join([self.__trace_file])

    def process(self):
        for fl in self.__target:
            if len(fl) == 1:
                continue
            self.calc(fl)

    def calc(self, func_list):
        permutations = itertools.permutations(func_list, len(func_list))
        key = SubsequenceProcessor.get_key(func_list)
        filename = ''.join([self.__result_file, '.', key])
        result = []
        with open(self.__trace_file, "r") as f:
            lines = f.readlines()
            for permutation in permutations:
                num = 0
                for line in lines:
                    line = parse_line(line)
                    num += self.__match_permutation(line, permutation)
                result.append(num)

                if len(result) > 10000:
                    self.__save(filename, ', '.join([str(i) for i in result]) + ', ')
                    result = []
            self.__save(filename, ', '.join([str(i) for i in result]) + '\n')

    def __match_permutation(self, line, permutation):
        idx = 0
        length = len(line)
        for func in permutation:
            while idx < length:
                fn = line[idx]
                if fn == func:
                    idx += 1
                    break
                idx += 1
            else:
                # can not find the next function
                return 0
        else:
            # find all
            return 1

    def __save(self, file, content):
        """
        save the content
        """
        with open(file, 'a') as f:
            f.write(content)


if __name__ == "__main__":
    arg_parser = argparse.ArgumentParser(description="Calculate subsequence")
    arg_parser.add_argument("-f", "--filename", help="file base name", required=True)
    arg_parser.add_argument("-s", "--funcset", help="function set", required=True)
    args = arg_parser.parse_args()

    # ranking_funcs = read_ranking_file(RANKING_FILE)

    funcs = args.funcset.split("-")
    SubsequenceProcessor([funcs], args.filename).process()





