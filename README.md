# Software Testing: Inventory Management System

This repository contains the final project deliverables for the Software Testing, Verification, and Validation course. It represents a comprehensive testing lifecycle conducted on a C++ Console-based Inventory Management System.

## Project Scope
The project involved conducting static design and implementation reviews, creating professional test planning documentation, integrating the Google Test (`gtest`) framework for automated unit testing, and applying ISTQB-standard black-box testing techniques.

### Original Source Code
The system being tested is derived from the "Inventory Management System" project in the following repository:
[mohamedsafy/SWTDemoProjects](https://github.com/mohamedsafy/SWTDemoProjects)

## Deliverables

| File | Description |
|------|-------------|
| **`ProjectReport.pdf`** | The comprehensive final report documenting methodology, findings, test results, and defect logs. |
| **`TestPlan.pdf`** | The master test plan detailing the testing strategy, scope, objectives, and environment needs. |
| **`ISTQB_TestDesign.xlsx`** | Formal test design derivations using Equivalence Partitioning (EP), Boundary Value Analysis (BVA), and Decision Tables. |
| **`FunctionalTestCases.xlsx`** | 21 meticulously crafted black-box test cases traced back to ISTQB techniques. |
| **`StaticReviewReport_Design.xlsx`** | Documentation of defects found in the system's class and sequence diagrams (e.g., UI coupling). |
| **`StaticReviewReport_Implementation.xlsx`** | Code-level reviews highlighting exception-handling bugs and data-loss vectors. |
| **`TraceabilityMatrix.xlsx`** | Requirement Traceability Matrix (RTM) proving 100% test coverage for all functional requirements. |
| **`DefectReport.xlsx`** | Log of system bugs discovered during dynamic execution. |
| **`tests/InventoryServiceTest.cpp`** | The suite of 20 automated unit tests written using the Google Test framework. |

## Key Findings
* **Critical Bug (BUG-01):** A silent data-loss vulnerability was identified in the JSON parsing exception handler, resulting in data loss if `inventory.json` is corrupted.
* **Architectural Flaws:** Static design review identified direct coupling between the UI (`InventoryConsole`) and Data Persistence (`InventoryRepository`) layers.
* **Test Results:** 100% pass rate achieved for the isolated business logic layer (20/20 `gtest` unit tests passed). Functional UI testing successfully identified boundary failures (trailing whitespaces).
