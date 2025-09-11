#O(2n) time
#O(n) space
def rotate(self, nums: list[int], k: int) -> None:
    """
    Do not return anything, modify nums in-place instead.
    """
    dic = {}

    for i in range(len(nums)):
        newPos = (i + k)%len(nums)
        dic[newPos] = nums[i]
    
    for i in range(len(nums)):
        nums[i] = dic[i]

#O(1) space
def rotate(self, nums: list[int], k: int) -> None:
    """
    Do not return anything, modify nums in-place instead.
    """
    nums[:] = nums[-(k % len(nums)):] + nums[:-(k % len(nums))]