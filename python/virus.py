import numpy as np
import matplotlib.pyplot as plt


class VirusSimulator(object):
    def __init__(self):

        # 地图宽度
        self.width = 100

        # 总人口
        self.pop = 5000

        # 初始病人数量
        self.first_patients = 10

        # 感染半径
        self.infection_radius = 5

        # 感染几率 50%
        self.infection_potential = 0.5

        # 人群：横坐标、纵坐标
        self.locations = np.random.randn(self.pop, 2) * self.width

        # 状态：（g-正常、r-感染）
        self.status = np.array(["g"] * self.pop)

        # 初始化感染群
        self.initPatients()

    # 更新人群位置
    def move(self):
        self.locations += np.random.randn(self.pop, 2)

    # 初始化患病人群
    def initPatients(self):
        for i in np.random.randint(self.pop, size=self.first_patients):
            if self.status[i] == "g":
                self.status[i] = "r"

    # 统计感染人群
    @property
    def patients(self):
        return self.locations[self.status == "r"]

    # 统计感染人数
    @property
    def patients_num(self):
        return self.status[self.status == "r"].size

    # 传染函数
    def affect(self):
        for ip in self.patients:
            distances = np.sqrt(np.sum(np.asarray(ip - self.locations)**2, axis=1))
            self.status[distances < self.infection_radius] = "r"

    # 显示函数
    def display(self):
        current_patient_num = self.patients_num
        print("总人数：{}，传染人数：{}".format(self.pop, current_patient_num))
        plt.ion()

        while current_patient_num < self.pop:
            plt.clf()
            plt.scatter(self.locations[:, 0], self.locations[:, 1], c=self.status, s=1)
            plt.axis([-self.width, self.width, -self.width, self.width])
            self.move()
            self.affect()
            current_patient_num = self.patients_num
            print("总人数：{}，传染人数：{}".format(self.pop, current_patient_num))
            plt.pause(0.5)

        plt.ioff()
        plt.show()


if __name__ == "__main__":
    vs = VirusSimulator()
    vs.display()