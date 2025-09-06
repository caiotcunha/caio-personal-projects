def mergeSort(array):
    if len(array) > 1:
        mid = len(array)//2
        #sides
        leftHalf = array[0:mid]
        rightHalf = array[mid:len(array)]

        #recursive call
        mergeSort(leftHalf)
        mergeSort(rightHalf)
        #merge
        i = 0
        j = 0
        k = 0

        while i < len(leftHalf) and j < len(rightHalf):
            if leftHalf[i] < rightHalf[j]:
                array[k] = leftHalf[i]
                i = i + 1
            else:
                array[k] = rightHalf[j]
                j = j + 1
            k = k + 1
        
        while i < len(leftHalf):
            array[k] = leftHalf[i]
            i = i + 1
            k = k + 1
        
        while j < len(rightHalf):
            array[k] = rightHalf[j]
            j = j + 1
            k = k + 1
        
        return array
    else:
        return array


if __name__ == "__main__":
    array = [444,78,12,30,24,31,80,55,90]
    ordered = mergeSort(array)
    print(ordered)