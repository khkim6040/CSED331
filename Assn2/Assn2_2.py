import math

def get_kth_value(arr, k):
    sorted_arr = sorted(arr)
    return sorted_arr[k-1]
    
def partition_into_five_elements(arr):
    partitions = []
    for x in range(0, len(arr), 5):
        partitions.append(arr[x:x+5])
    return partitions

def generate_medians(partitions):
    medians = []
    for arr in partitions:
        medians.append(get_kth_value(arr, len(arr)//2));
    return medians;

def median_of_medians(arr, k):
    if(len(arr) <= 5):
        return get_kth_value(arr, k)
    # partition arr into 5 elements sublist
    partitions = partition_into_five_elements(arr)
    # derive list of median of partitions
    medians = generate_medians(partitions)
    # get median of arr recursively
    median = median_of_medians(medians, len(medians)//2)
    
    # find which subarray contain kth element
    left = [x for x in arr if x<median]
    mid = [x for x in arr if x==median]
    right = [x for x in arr if x>median]
    
    if (k <= len(left)):
        return median_of_medians(left, k)
    elif (k > len(left)+len(mid)):
        return median_of_medians(right, k-len(left)-len(mid))
    else:
        return median
    
import sys
input = sys.stdin.readline

number_of_test_cases = int(input())
for _ in range(number_of_test_cases):
    median_index = math.ceil(int(input())/2)
    arr = list(map(int, input().split()))
    print(median_of_medians(arr, median_index))
    



