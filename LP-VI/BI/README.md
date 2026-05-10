## Viva Prep

### What is Business Intelligence (BI)? How is it different from traditional data analysis?

BI is a set of technologies, processes, and tools that collect, integrate, and analyze business data to support better decision-making.

Traditional data analysis is **reactive** — it answers "what happened?" BI is **proactive** — it answers "what happened, why, and what should we do next?" BI also includes dashboards, reporting, and real-time monitoring, whereas traditional analysis is typically one-time and manual.

---

### What are the major components of a BI architecture?

1. **Data Sources** — ERP, CRM, flat files, databases
2. **ETL Layer** — Extract, Transform, Load data into the warehouse
3. **Data Warehouse** — Central repository for integrated data
4. **OLAP / Analytics Engine** — For multidimensional analysis
5. **Reporting & Visualization Layer** — Dashboards, reports (Tableau, Power BI)
6. **End Users** — Analysts, managers, executives

---

### Can you explain the BI lifecycle?

Data Collection → Data Integration (ETL) → Data Storage (Data Warehouse) → Analysis (OLAP, Mining) → Reporting & Visualization → Decision Making → Feedback loop back to collection.

---

### What is a system? How do you define a DSS?

A **system** is a set of interrelated components working together toward a common goal.

A **DSS** is a computer-based information system that supports semi-structured and unstructured decision-making by providing data, models, and analytical tools to decision makers.

---

### What are the main components of a DSS?

1. **Database Management System (DBMS)** — stores relevant data
2. **Model Management System (MMS)** — contains mathematical/analytical models
3. **User Interface** — allows interaction between user and system
4. **Knowledge Base** *(in some models)* — domain-specific rules and expertise

---
### What is the role of a Data Warehouse in BI?

A data warehouse is the **central repository** of integrated, historical, and cleaned data that BI systems use for analysis. It consolidates data from multiple sources (ERP, CRM, flat files), making it query-ready for reporting and analytics. Without a data warehouse, BI tools would query operational databases directly — which is slow and risky for live systems.

---

### Operational vs Analytical Data

| | Operational | Analytical |
|---|---|---|
| **Purpose** | Day-to-day transactions | Decision making |
| **Data** | Current, real-time | Historical, aggregated |
| **Example** | Processing an order | Analyzing 1-year sales trend |
| **System** | OLTP | OLAP / Data Warehouse |
| **Users** | Clerks, operators | Managers, analysts |

---

### Descriptive vs Predictive vs Prescriptive Analytics

- **Descriptive** — *"What happened?"* → Sales reports, dashboards, historical summaries
- **Predictive** — *"What will happen?"* → ML models, forecasting, trend analysis
- **Prescriptive** — *"What should we do?"* → Optimization models, recommendation engines

Each builds on the previous. Most organizations start with descriptive and mature toward prescriptive.

---

### Four Stages of Simon's Decision-Making Process

1. **Intelligence** — Scanning the environment to identify the problem. *"Something is wrong — what is it?"*

2. **Design** — Developing and analyzing possible solutions. *"What are my options?"*

3. **Choice** — Selecting the best alternative from the options. *"Which solution do I go with?"*

4. **Implementation** — Executing the chosen solution and monitoring results. *"Put it into action and track outcomes."*

---

### Structured vs Semi-structured vs Unstructured Decisions

- **Structured** — Fully defined, repetitive, rule-based. *Example: Reordering inventory when stock drops below 100 units.*

- **Semi-structured** — Partially defined, requires some human judgment. *Example: Approving a loan application — rules exist but officer uses discretion.*

- **Unstructured** — No clear procedure, relies heavily on intuition and experience. *Example: Deciding whether to enter a new market or launch a new product.*

> DSS is most valuable for **semi-structured** decisions — structured ones are automated, unstructured ones are too ambiguous for pure data-driven answers. 

---
### What is OLAP? What problem does it solve?

OLAP stands for **Online Analytical Processing**. It is a technology that allows users to analyze large volumes of data from multiple perspectives quickly.

**Problem it solves:** Business users need to ask complex analytical questions like *"What were the sales of Product X in Region Y during Q3?"* — relational databases are too slow and rigid for this. OLAP provides fast, flexible, multidimensional analysis on historical data.

---

### What is OLTP?

**Online Transaction Processing** — systems designed to manage day-to-day business transactions like inserting orders, updating records, processing payments. Examples: banking systems, e-commerce order systems, POS systems.

---

### OLAP vs OLTP

| | OLTP | OLAP |
|---|---|---|
| **Purpose** | Transaction processing | Analytical queries |
| **Data** | Current, detailed | Historical, aggregated |
| **Operations** | INSERT, UPDATE, DELETE | SELECT, complex aggregations |
| **Users** | Clerks, operators | Analysts, managers |
| **Query Type** | Simple, predefined | Complex, ad hoc |
| **DB Size** | MB to GB | GB to TB |
| **Schema** | Normalized (3NF) | Denormalized (Star/Snowflake) |

---

### What is a Dimension in OLAP? Give three examples.

A **dimension** is a categorical perspective or axis along which data is analyzed.

Examples:
- **Time** — Year, Quarter, Month, Day
- **Geography** — Country, State, City
- **Product** — Category, Subcategory, SKU

---

### What is Multidimensional Analysis? Give a business example.

Multidimensional analysis means analyzing data across **multiple dimensions simultaneously** rather than one at a time.

**Example:** A retail company analyzes sales data across three dimensions — *Time* (Q1 2024), *Product* (Laptops), and *Region* (West India) — to find that laptop sales dropped 20% in West India in Q1. This insight comes from combining all three dimensions at once, which a simple SQL query on OLTP would struggle to do efficiently.

---

### Drill-down, Roll-up, Dice

**Drill-down** — Moving from **higher to lower** level of detail.
> Year → Quarter → Month → Day
> *"I see annual sales are low, let me drill down to see which month caused it."*

**Roll-up** — Opposite of drill-down. Moving from **lower to higher** level of aggregation.
> City → State → Country
> *"I have city-level data, roll up to see country-level totals."*

**Dice** — Selecting a **subcube** by fixing conditions on **multiple dimensions** simultaneously.
> Sales where Year = 2024 **AND** Region = West **AND** Product = Laptops
> *Dice cuts out a smaller cube from the larger cube.*

> **Slice vs Dice:** Slice fixes **one** dimension. Dice fixes **two or more** dimensions.

---

### Different OLAP Models

Three main models: **ROLAP, MOLAP, HOLAP**

---

#### ROLAP (Relational OLAP)
- Stores data in **relational databases** (standard SQL tables)
- Uses Star or Snowflake schema
- Generates SQL queries dynamically at runtime
- **Pros:** Highly scalable, handles large data
- **Cons:** Slower query performance compared to MOLAP

---

#### MOLAP (Multidimensional OLAP)
- Stores data in **proprietary multidimensional arrays** (pre-built cubes)
- Data is **pre-aggregated** at load time
- **Pros:** Very fast query response
- **Cons:** Limited scalability, high storage for sparse data

---

#### HOLAP (Hybrid OLAP)
- **Combination of ROLAP and MOLAP**
- Detailed data stays in relational storage (ROLAP), aggregated summaries stored in multidimensional arrays (MOLAP)
- **When to use:** When you need **both scalability and fast query performance** — large datasets where you still want quick access to aggregated views
- Best of both worlds but more complex to implement

---

> **One-line summary for viva:**
> ROLAP = scalable but slow. MOLAP = fast but limited. HOLAP = balanced but complex.

--
### What is a Star Schema?

A Star schema is the **simplest DW schema** where one central **Fact Table** is directly connected to multiple **Dimension Tables**. It looks like a star when drawn.

```
          [Time Dim]
               |
[Product Dim]--[FACT TABLE]--[Region Dim]
               |
          [Customer Dim]
```

- Dimension tables are **denormalized** — all attributes in one flat table
- Queries are **fast** because fewer joins are needed
- **Trades storage for speed**

---

### What is a Snowflake Schema? How is it different?

Snowflake schema is an **extension of Star schema** where dimension tables are **further normalized** into sub-dimension tables. It looks like a snowflake.

```
[City]→[State]→[Region Dim]--[FACT TABLE]--[Product Dim]→[Category]
```

| | Star | Snowflake |
|---|---|---|
| **Normalization** | Denormalized | Normalized |
| **Query Speed** | Faster | Slower (more joins) |
| **Storage** | More redundancy | Less redundancy |
| **Complexity** | Simple | Complex |
| **Maintenance** | Harder to update | Easier to update |

> **When to use Snowflake:** When storage is a constraint and data integrity matters more than query speed.

---

### What is a Fact Constellation (Galaxy Schema)?

A Fact Constellation is a schema with **multiple fact tables sharing common dimension tables**. It looks like a galaxy of stars.

```
[Time Dim]    [Product Dim]
     |        /         \
[FACT: Sales]         [FACT: Inventory]
              \         /
            [Region Dim]
```

**When is it used:**
- When the DW needs to support **multiple business processes** simultaneously
- Example: A retail DW tracking both **Sales** and **Inventory** facts, both sharing Time, Product, and Region dimensions
- More complex but gives a **complete enterprise-wide view**

---

### What is a Fact Table? What does it contain?

A Fact Table is the **central table** in a DW schema. It contains:

- **Foreign keys** pointing to each dimension table
- **Measures/Facts** — numerical, quantifiable business metrics

Example Fact Table for retail:

| time_id | product_id | region_id | sales_amount | units_sold | profit |
|---|---|---|---|---|---|
| 1 | 101 | 5 | 25000 | 200 | 5000 |

> Facts are typically **additive** (can be summed across all dimensions), **semi-additive** (summed across some), or **non-additive** (cannot be summed — e.g., ratios, percentages).

---

### What is a Dimension Table? Give examples in retail DW.

A Dimension Table provides the **descriptive context** for the facts. It answers the *who, what, where, when* around a measurement.

Examples in a retail Data Warehouse:

- **Time Dimension** — day, month, quarter, year, holiday flag
- **Product Dimension** — product name, category, subcategory, brand, supplier
- **Customer Dimension** — customer name, age, city, loyalty tier
- **Store/Region Dimension** — store name, city, state, region, store size

> **Key difference to remember:**
> Fact table has **numbers you calculate with**.
> Dimension table has **attributes you filter and group by**.

---
### What are KPIs? Give three examples in a retail business context.

**KPI (Key Performance Indicator)** is a measurable value that indicates how effectively an organization is achieving its business objectives. In BI, KPIs are displayed on dashboards to give decision makers a quick health check of the business.

Three examples in retail:

1. **Sales Revenue per Store** — measures how much revenue each store generates; helps identify underperforming locations
2. **Inventory Turnover Rate** — measures how fast stock is sold and replaced; low rate indicates overstocking or weak demand
3. **Customer Acquisition Cost (CAC)** — measures how much is spent to acquire each new customer; helps evaluate marketing efficiency

---

### Four Popular BI Tools

| Tool | Distinguishing Feature |
|---|---|
| **Tableau** | Best-in-class **data visualization**; drag-and-drop interface, minimal SQL knowledge needed |
| **Microsoft Power BI** | Deep **Microsoft ecosystem integration** (Excel, Azure, Teams); cost-effective for enterprises |
| **Qlik Sense** | **Associative data model** — lets users explore data freely without predefined query paths |
| **Looker** | **LookML modeling layer** — defines business metrics in code, ensuring consistent definitions across the org |

> **One-line tip for viva:**
> If asked which is most popular in industry — say **Power BI** for enterprises, **Tableau** for analytics-heavy teams, and **Looker** is dominant where Google Cloud is the infrastructure.

---
### What is a Data Mart? How does it differ from a Data Warehouse?

A **Data Mart** is a **subject-specific subset** of a Data Warehouse focused on a particular business unit or function.

| | Data Warehouse | Data Mart |
|---|---|---|
| **Scope** | Enterprise-wide | Department-specific |
| **Data** | All business functions | Single subject (Sales, HR, Finance) |
| **Size** | Very large (TB) | Smaller (GB) |
| **Users** | Entire organization | Specific team/department |
| **Build Time** | Months | Weeks |
| **Cost** | High | Low |

Two types:
- **Dependent Data Mart** — sourced directly from the central Data Warehouse
- **Independent Data Mart** — sourced directly from operational systems, bypassing DW

> **Simple analogy:** Data Warehouse is the **supermarket** (everything). Data Mart is the **specific aisle** (just dairy, just produce).

---

### Which BI Tools am I Familiar With?

For viva purposes, claim familiarity with **Power BI and Tableau** as they are most commonly taught. Be honest about depth — say:

> *"I have worked with Power BI for creating dashboards and reports, and I have explored Tableau for visualization. I understand the core concepts of Looker as well."*

---

### How Does Power BI Connect to Different Data Sources?

Power BI connects via **Get Data** option which supports:

- **Files** — Excel, CSV, JSON, XML
- **Databases** — SQL Server, MySQL, PostgreSQL, Oracle
- **Cloud Services** — Azure, Google Analytics, Salesforce
- **Online Services** — SharePoint, Dynamics 365
- **APIs / Web** — REST APIs, OData feeds

Connection modes:
- **Import** — data is copied into Power BI's in-memory engine (fast, but not real-time)
- **DirectQuery** — queries run live against the source (real-time, but slower)
- **Live Connection** — used specifically for Analysis Services

---

### Process of Creating a Dashboard in Tableau

1. **Connect to Data Source** — Excel, SQL, cloud, etc.
2. **Prepare Data** — join tables, create calculated fields, handle nulls in Data Source tab
3. **Build Worksheets** — drag dimensions and measures onto Rows/Columns shelf, choose chart type
4. **Apply Filters and Parameters** — filter by region, time, category etc.
5. **Create Dashboard** — drag multiple worksheets onto a dashboard canvas
6. **Add Interactivity** — add filters, actions (filter action, highlight action, URL action)
7. **Publish** — publish to Tableau Server or Tableau Public for sharing

---

### Power BI vs Tableau

| | Power BI | Tableau |
|---|---|---|
| **Vendor** | Microsoft | Salesforce |
| **Cost** | Cheaper (Pro ~$10/user/month) | More expensive |
| **Ease of Use** | Easier for Microsoft users | Steeper learning curve |
| **Visualization** | Good | Superior, more flexible |
| **Data Prep** | Power Query (strong) | Tableau Prep (decent) |
| **Integration** | Deep Microsoft ecosystem | Broader data source support |
| **Language** | DAX, M | VizQL, calculated fields |
| **Best For** | Enterprise, Office 365 users | Analytics-heavy, data teams |

> **One-line answer if pressed:** *"Power BI wins on cost and Microsoft integration. Tableau wins on visualization flexibility and depth of analytics."*

---
### What is a Data Mart? *(already covered above — quick recap)*

A Data Mart is a **department-specific subset** of a Data Warehouse. DW = enterprise-wide, Data Mart = single subject area like Sales or HR.

---

### Types of Analytics

**Descriptive** — *"What happened?"*
- Looks at historical data to summarize past events
- Tools: reports, dashboards, charts
- Example: *Monthly sales report for Q3 2024*

**Diagnostic** — *"Why did it happen?"*
- Drills deeper into data to find root cause
- Example: *Sales dropped in Q3 — was it pricing, competition, or supply issues?*

**Predictive** — *"What will happen?"*
- Uses ML models, statistical forecasting on historical patterns
- Example: *Predicting next quarter's demand using past trends*

**Prescriptive** — *"What should we do?"*
- Recommends actions based on predictions
- Example: *Recommending optimal pricing strategy to maximize revenue*

> Each level builds on the previous. Most organizations start at descriptive and mature upward. Most advanced BI systems today aim for prescriptive.

---

### How Can BI Support Decision-Making?

1. **Single source of truth** — all departments work from the same consistent data, eliminating conflicts
2. **Real-time dashboards** — managers get instant visibility into KPIs without waiting for reports
3. **Ad hoc querying** — analysts can ask any business question without IT involvement
4. **Trend identification** — BI surfaces patterns humans would miss in raw data
5. **Risk reduction** — data-driven decisions reduce gut-feel errors
6. **Supports all levels** — operational (daily decisions), tactical (monthly planning), strategic (annual goals)

> **One-line summary:** BI converts raw data into actionable insights, enabling faster, more accurate, and more confident decisions at every level of the organization.

---

### BI in Different Sectors

---

#### 🏥 Healthcare
- **Patient outcome analysis** — tracking treatment success rates across hospitals
- **Bed occupancy dashboards** — real-time monitoring of available beds
- **Readmission prediction** — predicting which patients are likely to return within 30 days
- **Resource allocation** — optimizing staff scheduling based on patient load patterns
- **Fraud detection** — identifying anomalous insurance claims

---

#### 🛒 Retail
- **Sales trend analysis** — identifying best and worst performing products by region and season
- **Inventory optimization** — preventing overstock and stockouts using demand forecasting
- **Customer segmentation** — grouping customers by purchase behavior for targeted marketing
- **Basket analysis** — finding which products are frequently bought together (Market Basket Analysis)
- **Store performance dashboards** — comparing KPIs across all store locations in real time

---

#### 🏦 Finance
- **Risk analytics** — assessing credit risk and loan default probability
- **Fraud detection** — identifying unusual transaction patterns in real time
- **Portfolio performance tracking** — dashboards showing return on investment across assets
- **Regulatory compliance reporting** — automating reports required by RBI, SEBI, etc.
- **Customer profitability analysis** — identifying which customers generate the most value

---

> **Tip for viva:** If the examiner asks for a sector-specific example, always give **one concrete use case + the BI tool/technique used**. Example: *"In retail, Market Basket Analysis using association rules helps identify product pairs for cross-selling — this is prescriptive analytics driven by BI."*

---
### What is Data Validation? Why is it critical before BI analysis?

Data validation is the process of **checking data for accuracy, completeness, and consistency** before it enters the BI pipeline.

It is critical because:
- BI decisions are only as good as the data behind them — **"Garbage in, garbage out"**
- Invalid data leads to incorrect reports, wrong KPIs, and bad business decisions
- Catching errors early is cheaper than fixing them after analysis

---

### Techniques to Handle Noisy Data

**Binning:**
- Sort data and divide into equal-frequency or equal-width bins
- Smooth values by replacing with bin mean, median, or boundary values
- Example: Ages 23, 25, 27 in a bin → all replaced with mean 25

**Regression Smoothing:**
- Fit a regression function to the data
- Values that deviate significantly from the regression line are considered noise
- Works well when noise follows a pattern

**Clustering-based Detection:**
- Group data points into clusters
- Points that don't belong to any cluster are flagged as noise/outliers
- Example: DBSCAN algorithm naturally identifies noise points

---

### What is Data Quality? Four Dimensions:

Data quality means data is **fit for its intended use** in BI and decision making.

- **Accuracy** — data correctly represents reality. *(Age = 250 is inaccurate)*
- **Completeness** — no missing values where values are expected. *(Customer record with no phone number)*
- **Consistency** — same data across different systems matches. *(DOB differs in CRM vs HR system)*
- **Timeliness** — data is up-to-date and available when needed. *(Yesterday's sales data available today morning)*

---

### What is Data Transformation? Why is it needed?

Data transformation is the process of **converting raw data into a format suitable for analysis and modeling.**

It is needed because:
- Different features may be on **different scales** — confusing models
- Some algorithms require **normally distributed** data
- Categorical data must be converted to **numerical** form for ML models
- Raw data may have **skewed distributions** that hurt model performance

Common transformations: standardization, normalization, encoding, log transformation, feature extraction.

---

### Standardization vs Normalization

**Standardization:**
> z = (x - μ) / σ
- Centers data around mean=0, std=1
- No fixed output range
- **Use when:** data has outliers, algorithm assumes normally distributed data (SVM, PCA, Linear Regression)

**Normalization (Min-Max Scaling):**
> x' = (x - min) / (max - min)
- Scales data to fixed range **[0, 1]**
- Sensitive to outliers
- **Use when:** algorithm needs bounded input (Neural Networks, KNN)

| | Standardization | Normalization |
|---|---|---|
| **Output Range** | No fixed range | 0 to 1 |
| **Outlier Sensitivity** | Low | High |
| **Best For** | PCA, SVM, LR | KNN, Neural Nets |

> **Simple rule:** If you don't know which to use — **standardize**. It is more robust.

---

### What is Data Reduction? Why is it needed?

Data reduction is the process of **reducing the volume of data while preserving its analytical value.**

Needed because:
- Large datasets slow down processing and modeling
- High dimensionality causes **curse of dimensionality**
- Many features may be **redundant or irrelevant**
- Reduces storage and computational cost without significant loss of information

Techniques: Sampling, Feature Selection, PCA, Data Discretization.

---

### What is PCA (Principal Component Analysis)?

PCA is a **dimensionality reduction technique** that transforms high-dimensional data into a smaller set of new variables called **Principal Components** while retaining maximum variance.

**How it works — in simple steps:**
1. Standardize the data
2. Compute the **covariance matrix**
3. Find **eigenvectors and eigenvalues** of the covariance matrix
4. Sort eigenvectors by eigenvalue — highest = most variance captured
5. Select top k eigenvectors as principal components
6. Project original data onto these components

**Key points:**
- Principal components are **not original features** — they are linear combinations of them
- Each component is **orthogonal** (uncorrelated) to the others
- First PC captures **maximum variance**, second captures next most, and so on
- You decide how many components to keep by targeting ~95% explained variance

**Tradeoff:**
> PCA reduces dimensionality but **loses interpretability** — you can no longer say "this feature caused this outcome" because components are abstract combinations.

> **One-line answer:** *"PCA finds new axes in the data that capture maximum variance, allowing us to represent data in fewer dimensions without losing significant information."*

---

### Data Exploration

Data exploration is the **initial investigation of data** to understand its structure, patterns, distributions, and relationships before building models or dashboards.

It has three levels:

---

## 1. Univariate Analysis
*"Analyze ONE variable at a time"*

The simplest form — you look at each feature **independently** to understand its distribution, central tendency, and spread. No relationships between variables are studied here.

---

### For Categorical Attributes

**Graphical methods:**
- **Bar Chart** — shows frequency of each category
- **Pie Chart** — shows proportion of each category
- **Frequency Table** — count and percentage of each category value

**Example:** Analyzing "Payment Method" column — Cash: 40%, Card: 35%, UPI: 25%

---

### For Numerical Attributes

**Graphical methods:**
- **Histogram** — shows distribution/shape of data
- **Box Plot** — shows spread, median, quartiles, outliers
- **Density Plot** — smooth version of histogram
- **Stem and Leaf Plot** — shows actual data values and distribution

---

### Measures of Central Tendency

These tell you **where the center of data lies.**

- **Mean** — arithmetic average
  > x̄ = Σx / n
  > Sensitive to outliers

- **Median** — middle value when sorted
  > Not affected by outliers
  > Use when data is skewed

- **Mode** — most frequently occurring value
  > Only measure applicable to categorical data

> **Rule:** If mean > median → positively skewed. If mean < median → negatively skewed.

---

### Measures of Dispersion

These tell you **how spread out the data is.**

- **Range** = Max - Min
  > Simplest but highly sensitive to outliers

- **Variance** = Σ(x - x̄)² / n
  > Average squared deviation from mean

- **Standard Deviation** = √Variance
  > Most commonly used; same unit as data

- **IQR (Interquartile Range)** = Q3 - Q1
  > Measures spread of middle 50% of data
  > Robust to outliers

---

### Outlier Identification

Using IQR method:
> **Lower bound** = Q1 - 1.5 × IQR
> **Upper bound** = Q3 + 1.5 × IQR
> Any value outside these bounds = **outlier**

Using Box Plot:
- Points plotted beyond whiskers are outliers
- Visually intuitive and quick

---

## 2. Bivariate Analysis
*"Analyze TWO variables together"*

Studies the **relationship between two variables** — how one changes with respect to the other.

---

### For Two Numerical Variables

**Graphical methods:**
- **Scatter Plot** — plots one variable on X-axis, other on Y-axis; reveals direction and strength of relationship
- **Line Chart** — used when one variable is time

**Measures of Correlation:**

**Pearson's Correlation Coefficient (r):**
> r = Σ(x - x̄)(y - ȳ) / √[Σ(x-x̄)² × Σ(y-ȳ)²]
> Range: **-1 to +1**

| Value | Meaning |
|---|---|
| r = +1 | Perfect positive correlation |
| r = -1 | Perfect negative correlation |
| r = 0 | No linear correlation |
| 0.7 to 1 | Strong positive |
| 0 to 0.3 | Weak positive |

**Covariance:**
> Measures direction of relationship but NOT strength
> Correlation = standardized covariance

> **Critical distinction:** *"Correlation does not imply causation"* — Ice cream sales and drowning rates are correlated but one doesn't cause the other (both caused by summer).

---

### For Two Categorical Variables

**Contingency Table (Cross Tabulation):**
- A table showing frequency distribution of two categorical variables simultaneously

Example — Gender vs Purchase Decision:

| | Bought | Did Not Buy |
|---|---|---|
| **Male** | 120 | 80 |
| **Female** | 150 | 50 |

**Chi-Square Test:**
- Tests whether two categorical variables are **independent or associated**
- If p-value < 0.05 → variables are **statistically associated**

---

### For One Categorical + One Numerical Variable

**Graphical methods:**
- **Grouped Bar Chart** — compare numerical measure across categories
- **Box Plot per Category** — compare distributions across groups
- **Violin Plot** — shows distribution shape per category

---

## 3. Multivariate Analysis
*"Analyze THREE or more variables together"*

Studies **complex relationships and interactions** among multiple variables simultaneously. This is where real-world BI insights emerge.

---

### Graphical Methods

- **Pair Plot (Scatter Matrix)** — scatter plot of every variable against every other variable in one grid; gives a complete relationship overview at a glance

- **Heatmap (Correlation Matrix)** — color-coded matrix showing correlation between all numerical variable pairs; dark red = strong positive, dark blue = strong negative

- **Parallel Coordinates Plot** — each variable is a vertical axis; each data point is a line connecting its values across all axes; useful for spotting clusters and patterns

- **3D Scatter Plot** — visualizes three numerical variables simultaneously in 3D space

---

### Measures of Correlation for Multiple Variables

**Correlation Matrix:**
- Computes Pearson's r between **every pair** of numerical variables
- Result is a symmetric n×n matrix
- Diagonal is always 1 (variable perfectly correlates with itself)

Example for a retail dataset:

| | Sales | Price | Discount |
|---|---|---|---|
| **Sales** | 1.00 | -0.72 | 0.65 |
| **Price** | -0.72 | 1.00 | -0.45 |
| **Discount** | 0.65 | -0.45 | 1.00 |

> Reading: Sales and Price have strong negative correlation (-0.72) — as price increases, sales drop.

**Multicollinearity:**
- When two or more independent variables are **highly correlated with each other**
- Problem for regression models — inflates variance, makes coefficients unstable
- Detected using correlation matrix or **VIF (Variance Inflation Factor)**
- VIF > 10 → severe multicollinearity → drop or combine those features

---

### Summary Table

| | Univariate | Bivariate | Multivariate |
|---|---|---|---|
| **Variables** | 1 | 2 | 3 or more |
| **Purpose** | Understand distribution | Find relationships | Find complex patterns |
| **Key Graph** | Histogram, Box Plot | Scatter Plot | Pair Plot, Heatmap |
| **Key Measure** | Mean, Std Dev | Correlation (r) | Correlation Matrix |
| **Question answered** | What does this variable look like? | Are these two related? | How do all variables interact? |

> **One-line viva answer if asked to distinguish:**
> *"Univariate tells you about one variable, bivariate tells you how two variables relate, and multivariate tells you how the entire feature space interacts — each level adds more analytical depth."*