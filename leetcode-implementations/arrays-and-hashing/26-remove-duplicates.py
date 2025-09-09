def removeDuplicates(self, nums: list[int]) -> int:
    # nums ta em ordem crescente
    k = 1
    l = 0
    for r in range(1,len(nums)):
        if nums[l] != nums[r]:
            l += 1
            k += 1
            nums[l],nums[r] = nums[r],nums[l]

    return k