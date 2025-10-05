import csv
import random
from google.colab import files

companies_by_country = {
    'India': {
        'Tata Motors': ['Cars'],
        'Mahindra': ['Cars', 'Tractors'],
        'Flipkart': ['E-commerce'],
        'Reliance': ['Retail', 'Telecom'],
        'Bajaj': ['Motorcycles'],
        'Godrej': ['Home Appliances'],
        'Infosys': ['Software'],
        'Wipro': ['Software'],
        'HCL': ['Software'],
        'Maruti Suzuki': ['Cars']
    },
    'USA': {
        'Apple': ['Smartphones', 'Laptops', 'Tablets'],
        'Microsoft': ['Software', 'Gaming Consoles', 'Tablets'],
        'Ford': ['Cars'],
        'General Motors': ['Cars'],
        'Dell': ['Laptops', 'Computers'],
        'HP': ['Laptops', 'Printers'],
        'Amazon': ['E-commerce', 'Smart Home', 'Electronics'],
        'Tesla': ['Cars'],
        'Boeing': ['Aircraft'],
        'Nike': ['Shoes', 'Clothing']
    },
    'Japan': {
        'Toyota': ['Cars'],
        'Honda': ['Cars', 'Motorcycles'],
        'Sony': ['Electronics', 'Gaming Consoles', 'Cameras'],
        'Panasonic': ['Electronics', 'Home Appliances'],
        'Nintendo': ['Gaming Consoles'],
        'Canon': ['Cameras'],
        'Nikon': ['Cameras'],
        'Fujitsu': ['Computers'],
        'Mitsubishi': ['Cars', 'Electronics'],
        'Yamaha': ['Musical Instruments', 'Motorcycles']
    },
    'South Korea': {
        'Samsung': ['Smartphones', 'Electronics', 'Home Appliances'],
        'LG': ['Electronics', 'Home Appliances'],
        'Hyundai': ['Cars'],
        'Kia': ['Cars'],
        'SK Hynix': ['Semiconductors'],
        'CJ Group': ['Food Products'],
        'Naver': ['Internet Services'],
        'Kakao': ['Internet Services'],
        'Lotte': ['Retail'],
        'Posco': ['Steel Products']
    },
    'Russia': {
        'Gazprom': ['Energy'],
        'Lukoil': ['Energy'],
        'Rosneft': ['Energy'],
        'Yandex': ['Internet Services'],
        'Kaspersky': ['Software'],
        'Aeroflot': ['Airlines'],
        'Sberbank': ['Financial Services'],
        'AvtoVAZ': ['Cars'],
        'Kamaz': ['Trucks'],
        'Rostec': ['Industrial']
    },
    'Canada': {
        'Shopify': ['E-commerce'],
        'Bombardier': ['Aircraft', 'Transportation'],
        'BlackBerry': ['Software', 'Smartphones'],
        'Lululemon': ['Clothing'],
        'Magna International': ['Automotive Parts'],
        'Suncor Energy': ['Energy'],
        'Telus': ['Telecom'],
        'RIM': ['Software'],
        'Air Canada': ['Airlines'],
        'Hudson\'s Bay': ['Retail']
    },
    'EU': {
        'Volkswagen': ['Cars'],
        'Daimler': ['Cars'],
        'BMW': ['Cars'],
        'Siemens': ['Electronics', 'Industrial'],
        'Philips': ['Electronics', 'Home Appliances'],
        'Airbus': ['Aircraft'],
        'Unilever': ['Consumer Goods'],
        'Nestlé': ['Food Products'],
        'LVMH': ['Luxury Goods'],
        'SAP': ['Software']
    },
    'Australia': {
        'BHP': ['Mining'],
        'Rio Tinto': ['Mining'],
        'Commonwealth Bank': ['Financial Services'],
        'Telstra': ['Telecom'],
        'Woolworths': ['Retail'],
        'Qantas': ['Airlines'],
        'Atlassian': ['Software'],
        'Fortescue Metals': ['Mining'],
        'Coles Group': ['Retail'],
        'Macquarie Group': ['Financial Services']
    },
    'China': {
        'Huawei': ['Smartphones', 'Telecom Equipment'],
        'Alibaba': ['E-commerce'],
        'Tencent': ['Internet Services'],
        'Xiaomi': ['Electronics', 'Smartphones'],
        'Lenovo': ['Computers', 'Smartphones'],
        'BYD': ['Cars'],
        'Geely': ['Cars'],
        'Haier': ['Home Appliances'],
        'DJI': ['Drones'],
        'Sinopec': ['Energy']
    },
    'UK': {
        'BP': ['Energy'],
        'Shell': ['Energy'],
        'Unilever': ['Consumer Goods'],
        'AstraZeneca': ['Pharmaceuticals'],
        'Vodafone': ['Telecom'],
        'HSBC': ['Financial Services'],
        'Barclays': ['Financial Services'],
        'Jaguar Land Rover': ['Cars'],
        'Rolls-Royce': ['Aerospace'],
        'GlaxoSmithKline': ['Pharmaceuticals']
    }
}

price_ranges = {
    'Cars': {
        'Tata Motors': (700000, 1500000),
        'Mahindra': (800000, 2000000),
        'Maruti Suzuki': (400000, 1200000),
        'Ford': (2000000, 5000000),
        'Tesla': (4000000, 10000000),
        'Toyota': (2000000, 5000000),
        'Honda': (1800000, 3500000),
        'BMW': (5000000, 15000000),
        'Daimler': (6000000, 18000000),
        'Hyundai': (1500000, 3500000),
        'Volkswagen': (3000000, 8000000),
        'Jaguar Land Rover': (6000000, 15000000),
        'BYD': (2000000, 5000000),
        'Geely': (1800000, 4000000),
        'AvtoVAZ': (500000, 2000000),
        'Kamaz': (2000000, 6000000),
    },
    'Smartphones': {
        'Apple': (50000, 150000),
        'Samsung': (20000, 100000),
        'Huawei': (15000, 80000),
        'Xiaomi': (10000, 50000),
        'Google': (40000, 120000),
        'Lenovo': (15000, 60000),
        'BlackBerry': (25000, 70000),
    },
    'Laptops': {
        'Apple': (100000, 300000),
        'Dell': (50000, 200000),
        'HP': (40000, 150000),
        'Lenovo': (40000, 150000),
        'Microsoft': (80000, 250000),
        'Samsung': (50000, 180000),
        'Huawei': (40000, 120000),
    },
    'Home Appliances': {
        'Samsung': (5000, 150000),
        'LG': (3000, 120000),
        'Haier': (4000, 100000),
        'Godrej': (5000, 120000),
        'Bosch': (10000, 150000),
        'Whirlpool': (8000, 140000),
        'Panasonic': (7000, 100000),
    },
    'Gaming Consoles': {
        'Sony': (25000, 50000),
        'Microsoft': (30000, 60000),
        'Nintendo': (20000, 40000),
    },
    'E-commerce': {
        'Amazon': (100, 2000),
        'Flipkart': (100, 1500),
        'Alibaba': (100, 1800),
        'Shopify': (200, 3000),
    },
    'Food Products': {
        'Nestlé': (20, 500),
        'CJ Group': (50, 400),
        'Unilever': (100, 500),
    },
    'Energy': {
        'Gazprom': (50000, 500000),
        'Lukoil': (60000, 550000),
        'Sinopec': (70000, 600000),
        'BP': (80000, 700000),
        'Shell': (90000, 750000),
        'Rosneft': (50000, 500000),
    },
    'Aircraft': {
        'Boeing': (100000000, 300000000),
        'Airbus': (120000000, 350000000),
        'Bombardier': (80000000, 250000000),
        'Rolls-Royce': (100000000, 300000000),
    },
    'Mining': {
        'BHP': (1000000, 5000000),
        'Rio Tinto': (1100000, 5100000),
        'Fortescue Metals': (1200000, 5200000),
    },
    'Telecom': {
        'Reliance': (100, 1000),
        'Telstra': (150, 1200),
        'Vodafone': (200, 1500),
    },
}

def generate_csv():
    with open('ecom.csv', 'w', newline='', encoding='utf-8') as csvfile:
        fieldnames = ['ProductID', 'Name', 'Company', 'Category', 'Country', 'Price', 'Views']
        writer = csv.DictWriter(csvfile, fieldnames=fieldnames)
        writer.writeheader()

        product_id = 1
        for country, companies in companies_by_country.items():
            for company, categories in companies.items():
                for category in categories:
                    for i in range(10):
                        product_name = f"{company} {category} {i + 1}"
                        price_range = price_ranges.get(category, {}).get(company, (1000, 50000))
                        price = round(random.uniform(*price_range), 2)
                        views = random.randint(1000, 25000)

                        writer.writerow({
                            'ProductID': product_id,
                            'Name': product_name,
                            'Company': company,
                            'Category': category,
                            'Country': country,
                            'Price': price,
                            'Views': views
                        })
                        product_id += 1

    print("ecom.csv file generated successfully.")

def download_csv():
    files.download('ecom.csv')

generate_csv()
download_csv()
