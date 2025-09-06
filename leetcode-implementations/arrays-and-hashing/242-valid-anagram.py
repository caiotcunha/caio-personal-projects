def isAnagram(s: str, t: str) -> bool:
    if len(s) != len(t):
        return False
    else:
        d = dict.fromkeys(s)
        for i in range(0,len(s)):
            d[s[i]] = 1 if d[s[i]] == None else d[s[i]] + 1
        
        for i in range(0,len(t)):
            if t[i] in d.keys():
                d[t[i]] -= 1
                if d[t[i]] < 0:
                    return False
            else:
                return False
        
        return True

def isAnagramCleaner(s: str, t: str) -> bool:
    if len(s) != len(t):
        return False

    countS, countT = {}, {}

    for i in range(len(s)):
        countS[s[i]] = 1 + countS.get(s[i], 0)
        countT[t[i]] = 1 + countT.get(t[i], 0)
    return countS == countT

if __name__ == "__main__":
    s="racecar"
    t="carrace"
    print(isAnagram(s, t))


