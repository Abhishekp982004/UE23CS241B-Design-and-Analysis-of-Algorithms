#include <stdio.h>
#include <stdbool.h>

// Function to find the largest mobile element
int getMobile(int n, int nums[], int dir[]) {
    int mobile = -1, mobileIndex = -1;
    
    for (int i = 0; i < n; i++) {
        if (dir[i] == 0 && i > 0 && nums[i] > nums[i - 1]) { // Moving left
            if (nums[i] > mobile) {
                mobile = nums[i];
                mobileIndex = i;
            }
        } else if (dir[i] == 1 && i < n - 1 && nums[i] > nums[i + 1]) { // Moving right
            if (nums[i] > mobile) {
                mobile = nums[i];
                mobileIndex = i;
            }
        }
    }
    return mobileIndex;
}

// Function to swap two elements
void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

// Johnson-Trotter algorithm implementation
void johnsonTrotter(int n, int nums[], int dir[], int k) {
    for (int step = 0; step < k; step++) {
        int mobileIndex = getMobile(n, nums, dir);
        if (mobileIndex == -1) { // No mobile element found
            printf("Permutation does not exist\n");
            return;
        }
        
        // Swap the mobile element in its direction
        int swapIndex = (dir[mobileIndex] == 0) ? mobileIndex - 1 : mobileIndex + 1;
        swap(&nums[mobileIndex], &nums[swapIndex]);
        swap(&dir[mobileIndex], &dir[swapIndex]);
        
        // Update mobile index after swap
        mobileIndex = swapIndex;
        
        // Reverse the direction of all elements greater than the moved element
        for (int i = 0; i < n; i++) {
            if (nums[i] > nums[mobileIndex]) {
                dir[i] ^= 1; // Toggle direction (0->1 or 1->0)
            }
        }
    }
    
    // Print the k-th permutation
    for (int i = 0; i < n; i++) {
        printf("%d ", nums[i]);
    }
    printf("\n");
}

int main() {
    int n, k;
    
    scanf("%d", &n);
    int nums[n];
    for (int i = 0; i < n; i++) {
        scanf("%d", &nums[i]);
    }
    
    int dir[n];
    for (int i = 0; i < n; i++) {
        scanf("%d", &dir[i]);
    }
    
    scanf("%d", &k);
    johnsonTrotter(n, nums, dir, k);
    
    return 0;
}
