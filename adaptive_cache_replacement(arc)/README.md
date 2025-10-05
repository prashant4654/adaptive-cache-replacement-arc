# BM2043 DSA LAB Project 1

![made-by-bm23btech11025-_-bm23btech11010](https://github.com/user-attachments/assets/71b7a612-1076-4f8e-836b-f8a904465fed)


![DSA](https://img.shields.io/badge/DSA-Lab_Project-orange.svg)
![C++](https://img.shields.io/badge/language-C++-blue.svg)

## E-Commerce Product Recommendation System

## Table of Contents

- [Introduction](#introduction)
- [Features](#features)
- [Technologies and Data Structures Used](#technologies-and-data-structures-used)
- [Code Overview](#code-overview)
- [Test Case Generation and Scalability](#test-case-generation-and-scalability)
- [Usage](#usage)
- [Menu Options](#menu-options)
- [About Team](#about-team)

## Introduction

The **E-Commerce Product Recommendation System** is a C++ project designed to manage and analyze product data for an e-commerce platform. It provides efficient operations for filtering, sorting, and recommending products based on various criteria such as price, category, views, or company.

## Features

- **Show All Products**: View all products with their details such as name, company, price, and views.
- **Top K Products by Views or Price**: Displays the most popular or expensive products.
- **Price Range Recommendations**: Retrieves products within a specific price range.
- **Filter Products by Category or Company**: Narrow down products based on user-defined category or company.
- **Sort Products**: Supports sorting by price or views in both ascending and descending orders.
- **Error Handling**: Detects and handles invalid data gracefully.

## Technologies and Data Structures Used

- **C++**: Core programming language.
- **Binary Search Tree (BST)**: Used to store products for efficient retrieval based on price range.
- **Priority Queue (Heap)**: Retrieves top K products by price or views quickly.
- **Vectors**: Handles collections of product data and sorting mechanisms.
- **File Handling**: Parses CSV files for product data with proper error handling.

## Code Overview

The project code is modular, focusing on clarity and performance:

- **Product Structure**: Represents each product with attributes such as `productID`, `name`, `company`, `category`, `price`, and `views`.
- **Binary Search Tree (BST)**: Implements efficient storage and querying of product data based on price.
- **File Parsing**: Reads product data from a CSV file and validates it.
- **Display and Filtering**: Provides formatted displays for all products and supports filtering by specific criteria.

## Test Case Generation and Scalability

To ensure the system's reliability and scalability, we generated a dataset of **1,000 products** using a Python script. Each product entry includes realistic and structured details such as product name, company, category, price, and views.

### Key Details:
- **Python Script**: The script generates random product details, including proper company names, categories, and price ranges.
- **File Name**: `E-commerce(data).csv` is the test dataset used in this project.
- **Sample Dataset**:

| ProductID | Name       | Company       | Category | Price  | Views |
|-----------|------------|---------------|----------|--------|-------|
| 1         | Indica 1   | Tata Motors   | Cars     | 1203.89 | 23067 |
| 2         | Nano 2     | Tata Motors   | Cars     | 101.24  | 4927  |
| 3         | Safari 3   | Tata Motors   | Cars     | 248.18  | 22910 |
| 4         | Nano 4     | Tata Motors   | Cars     | 773.44  | 7792  |
| 5         | Safari 5   | Tata Motors   | Cars     | 1663.79 | 16186 |

### Python Script Features:
- Generates random yet realistic product names using predefined adjectives and nouns.
- Ensures data integrity with categories and companies aligned for proper filtering and sorting.
- Outputs a CSV file that adheres to the project’s data parsing requirements.

**Please find the attached Python Script in Repositary**

## Usage

The application interacts via a menu-driven interface. Upon launching, the user can select operations like viewing products, getting recommendations, filtering by category or company, or sorting products.

### Menu Options

1. **Show All Products**: Lists all available products.
2. **Show Top K Products by Views**:
   - Prompts the user for the value of `K` to display the most viewed products.
3. **Show Top K Products by Price**:
   - Prompts the user for the value of `K` to display the most expensive products.
4. **Recommend Products in Price Range**:
   - Allows users to define a price range and shows products within that range.
5. **Filter Products by Category**:
   - Filters products based on their category (e.g., "Pharmaceuticals").
6. **Filter Products by Company**:
   - Filters products based on their manufacturer or company (e.g., "Nike").
7. **Sort Products**:
   - Offers options to sort by price or views in ascending or descending order.
8. **Exit**: Ends the program.

### Example Execution

#### Display All Products
Select option `1` to view all products with details such as:
- Product ID
- Name
- Company
- Category
- Price
- Views

#### Top K Products by Views or Price
1. Select option `2` or `3`.
2. Enter the desired value for `K`.
3. View the top K products based on views or price.

#### Filtering
- **Filter by Category**: Select option `5` and enter a category.
- **Filter by Company**: Select option `6` and enter a company name.

#### Sorting
- Select option `7` to sort by price or views.

## About Team

- **Created By**: Yashas & Kanna Ruthwik
- **BM23BTECH11025 | BM23BTECH11010**
- **GitHubs**: [BM23BTECH11025 (Yashas)](https://github.com/Roaryy) | [BM23BTECH11010 (Ruthwik)](https://github.com/Kanna-Ruthwik)
