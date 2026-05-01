#include <gtest/gtest.h>
#include "InventoryService.h"
#include "Product.h"
#include <vector>

class InventoryServiceTest : public ::testing::Test {
protected:
    InventoryService service;

    void SetUp() override {
        // Initialize with some dummy data if needed
        std::vector<Product> initialData = {
            {1, "Laptop", 10},
            {2, "Mouse", 50}
        };
        service.initialize(initialData);
    }
};

// Test initialization
TEST_F(InventoryServiceTest, InitializationLoadsProducts) {
    auto products = service.getAllProducts();
    ASSERT_EQ(products.size(), 2);
    EXPECT_EQ(products[0].name, "Laptop");
    EXPECT_EQ(products[1].quantity, 50);
}

// Test Adding a valid product
TEST_F(InventoryServiceTest, AddValidProduct) {
    Product newProduct = service.addProduct("Keyboard", 30);
    EXPECT_EQ(newProduct.id, 3);
    EXPECT_EQ(newProduct.name, "Keyboard");
    EXPECT_EQ(newProduct.quantity, 30);

    auto products = service.getAllProducts();
    ASSERT_EQ(products.size(), 3);
}

// Test Adding an invalid product (empty name)
TEST_F(InventoryServiceTest, AddInvalidProductEmptyName) {
    Product newProduct = service.addProduct("   ", 10);
    EXPECT_EQ(newProduct.id, 0); // System returns 0 for invalid

    auto products = service.getAllProducts();
    ASSERT_EQ(products.size(), 2); // Should not be added
}

// Test Adding an invalid product (negative quantity)
TEST_F(InventoryServiceTest, AddInvalidProductNegativeQuantity) {
    Product newProduct = service.addProduct("Monitor", -5);
    EXPECT_EQ(newProduct.id, 0);

    auto products = service.getAllProducts();
    ASSERT_EQ(products.size(), 2); // Should not be added
}

// Test Updating a product's quantity
TEST_F(InventoryServiceTest, UpdateProductQuantitySuccess) {
    bool result = service.updateProductQuantity(1, 25);
    EXPECT_TRUE(result);

    auto products = service.getAllProducts();
    EXPECT_EQ(products[0].quantity, 25);
}

// Test Updating a non-existent product
TEST_F(InventoryServiceTest, UpdateProductQuantityFailInvalidId) {
    bool result = service.updateProductQuantity(99, 10);
    EXPECT_FALSE(result);
}

// Test Searching for products
TEST_F(InventoryServiceTest, SearchProductsExactMatch) {
    auto results = service.searchProducts("Mouse");
    ASSERT_EQ(results.size(), 1);
    EXPECT_EQ(results[0].id, 2);
}

TEST_F(InventoryServiceTest, SearchProductsPartialIgnoreCase) {
    auto results = service.searchProducts("lap");
    ASSERT_EQ(results.size(), 1);
    EXPECT_EQ(results[0].name, "Laptop");
}

TEST_F(InventoryServiceTest, SearchProductsNoMatch) {
    auto results = service.searchProducts("Monitor");
    EXPECT_TRUE(results.empty());
}

// Test Removing a product
TEST_F(InventoryServiceTest, RemoveProductSuccess) {
    bool result = service.removeProduct(1);
    EXPECT_TRUE(result);

    auto products = service.getAllProducts();
    ASSERT_EQ(products.size(), 1);
    EXPECT_EQ(products[0].id, 2);
}

// Test Removing a non-existent product
TEST_F(InventoryServiceTest, RemoveProductFail) {
    bool result = service.removeProduct(99);
    EXPECT_FALSE(result);
}

// ============================================================
// ISTQB Boundary Value Analysis (BVA) Tests
// ============================================================

// BVA-AP-Q2: Add product with quantity exactly 0 (boundary)
TEST_F(InventoryServiceTest, BVA_AddProductZeroQuantity) {
    Product p = service.addProduct("Pencil", 0);
    EXPECT_NE(p.id, 0);  // Should succeed
    EXPECT_EQ(p.quantity, 0);
    EXPECT_EQ(service.getAllProducts().size(), 3);
}

// BVA-UP-ID1: Update with product ID = 0 (boundary, invalid)
TEST_F(InventoryServiceTest, BVA_UpdateWithZeroId) {
    bool result = service.updateProductQuantity(0, 10);
    EXPECT_FALSE(result);
}

// BVA-UP-Q2: Update quantity to exactly 0 (boundary, valid)
TEST_F(InventoryServiceTest, BVA_UpdateQuantityToZero) {
    bool result = service.updateProductQuantity(1, 0);
    EXPECT_TRUE(result);
    EXPECT_EQ(service.getAllProducts()[0].quantity, 0);
}

// BVA-RP-ID1: Remove with product ID = 0 (boundary, invalid)
TEST_F(InventoryServiceTest, BVA_RemoveWithZeroId) {
    bool result = service.removeProduct(0);
    EXPECT_FALSE(result);
    EXPECT_EQ(service.getAllProducts().size(), 2);  // Nothing removed
}

// BVA-RP-ID: Remove with negative product ID (boundary, invalid)
TEST_F(InventoryServiceTest, BVA_RemoveWithNegativeId) {
    bool result = service.removeProduct(-1);
    EXPECT_FALSE(result);
    EXPECT_EQ(service.getAllProducts().size(), 2);
}

// ============================================================
// ISTQB Decision Table Tests
// ============================================================

// DT-AP-R4: Add with BOTH invalid name AND negative quantity
TEST_F(InventoryServiceTest, DT_AddBothInvalid) {
    Product p = service.addProduct("", -3);
    EXPECT_EQ(p.id, 0);  // Rejected
    EXPECT_EQ(service.getAllProducts().size(), 2);  // Not added
}

// DT-UP-R4: Update with non-existing ID AND negative quantity
TEST_F(InventoryServiceTest, DT_UpdateBothInvalid) {
    bool result = service.updateProductQuantity(99, -5);
    EXPECT_FALSE(result);
}

// EP-SP-3: Search with empty query
TEST_F(InventoryServiceTest, EP_SearchEmptyQuery) {
    auto results = service.searchProducts("");
    EXPECT_TRUE(results.empty());
}

// EP-UP-ID3: Update with negative product ID
TEST_F(InventoryServiceTest, EP_UpdateWithNegativeId) {
    bool result = service.updateProductQuantity(-1, 10);
    EXPECT_FALSE(result);
}
