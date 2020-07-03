import threading

class Foobar:
    def __init__(self, n):
        self.n = n
        self.empty = threading.Lock()
        self.full = threading.Lock()
        self.full.acquire()

    def foo(self):
        for i in range(self.n):
            self.empty.acquire()
            print("foo", end='')
            self.full.release()

    def bar(self):
        for i in range(self.n):
            self.full.acquire()
            print("bar", end='')
            self.empty.release()

if __name__ == '__main__':
    fb = Foobar(4)
    t1 = threading.Thread(target=fb.foo)
    t2 = threading.Thread(target=fb.bar)

    t1.start()
    t2.start()