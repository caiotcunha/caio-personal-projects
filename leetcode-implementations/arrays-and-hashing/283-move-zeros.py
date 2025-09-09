def moveZeroes(self, nums: list[int]) -> None:
    """
    Do not return anything, modify nums in-place instead.
    """
    counter = 0
    for i,n in enumerate(nums):
        if n != 0:
            nums[i], nums[counter] = nums[counter], nums[i]
            counter = counter + 1