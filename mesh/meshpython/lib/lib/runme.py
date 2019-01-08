
import lib.meshOptimizer
import lib.meshreader
import lib.meshwriter


def main():
    data = lib.meshreader.read_values()
    temp = lib.meshOptimizer.optimize(data)
    lib.meshwriter.writeJson(temp)


if __name__ == '__main__':
    main()


# for key, value in data["xyz_with_index"].items():
#     if value[0] > -0.00001 and value[0] < 0.00001:
#         print(value[0])
#     if value[1] > -0.00001 and value[1] < 0.00001:
#         print(value[1])
#     if value[2] > -0.00001 and value[2] < 0.00001:
#         print(value[2])



