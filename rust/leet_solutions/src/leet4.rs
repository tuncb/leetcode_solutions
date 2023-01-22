//https://leetcode.com/problems/median-of-two-sorted-arrays/
pub fn leet4_find_median_two_arrays(nums1: Vec<i32>, nums2: Vec<i32>) -> f64 {
    return 0.0;
}

#[cfg(test)]
mod tests {
    use crate::leet4::leet4_find_median_two_arrays;

    #[test]
    fn test_leet4() {
        assert_eq!(leet4_find_median_two_arrays(vec![1, 3], vec![2]), 2.0);
        assert_eq!(leet4_find_median_two_arrays(vec![1, 2], vec![3, 4]), 2.5);
    }
}
