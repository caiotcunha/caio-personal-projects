def majorityElement(nums: list[int]) -> int:
    n = nums[0]
    s = 1
    for i in range(1,len(nums)):
        if s == 0:
            n = nums[i]
            s = 1
        else:
            s = s + 1 if nums[i] == n else s - 1
        
    return n