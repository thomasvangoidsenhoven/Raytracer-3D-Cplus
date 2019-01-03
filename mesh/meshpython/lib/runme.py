
import lib.meshOptimizer
import lib.meshreader
import lib.meshwriter


def main():
    data = lib.meshreader.read_values()
    temp = lib.meshOptimizer.optimize(data)
    lib.meshwriter.writeJson(temp)


if __name__ == '__main__':
    main()

