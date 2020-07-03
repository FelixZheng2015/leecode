from typing import List

class dayTemp:
    def __init__(self):
        print("Init a dayTemp instance")

    def dailyTemperatures(self, T:List[int]) -> List[int]:
        n = len(T)
        ans = [0] * n
        nxt = dict()
        big = 10 ** 9

        for i in range(n-1, -1, -1):
            warmer_index = min(nxt.get(t, big) for t in range(T[i]+1, 102))
            if warmer_index != big:
                ans[i] = warmer_index - i
            nxt[T[i]] = i
        return ans

    def test_dailyTemperatures(self) -> List[int]:
        T = [73, 74, 75, 71, 69, 72, 76, 73]
        return self.dailyTemperatures(T)
        