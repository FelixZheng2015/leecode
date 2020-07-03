class SolAddBinary:
    def addBinary(self, a, b) -> str:
        return '{:b}'.format(int(a,2)+int(b,2))

    def addBinary2(self, a, b) -> str:
        x = int(a, 2)
        y = int(b, 2)

        while y:
            answer = x ^ y
            carry = (x & y) << 1
            x, y = answer, carry

        return bin(x)[2:]

if __name__ == "__main__":
    item = SolAddBinary()
    output = item.addBinary2('1110', '10')
    print(output)