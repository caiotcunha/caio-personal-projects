def twoSum(nums: list[int], target: int) -> list[int]:
    map = {}
    for i, n in enumerate(nums):
        diff = target - n
        if diff in map:
            return [map[diff], i]
        map[n] = i

if __name__ == "__main__":
    nums = [3,4,5,6]
    target=7
    print(twoSum(nums, target))