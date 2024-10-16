import requests
import os

# Function to create a folder for storing images
def create_folder(folder_name):
    if not os.path.exists(folder_name):
        os.makedirs(folder_name)

# Function to download and save images
def download_image(url, folder_name, image_name):
    try:
        image_response = requests.get(url)
        if image_response.status_code == 200:
            with open(os.path.join(folder_name, image_name), 'wb') as img_file:
                img_file.write(image_response.content)
            print(f"Downloaded: {image_name}")
        else:
            print(f"Failed to download: {image_name}")
    except Exception as e:
        print(f"Error downloading {image_name}: {str(e)}")

# Function to get image URLs from Bing API
def bing_image_search(search_term, api_key, num_images=10):
    headers = {"Ocp-Apim-Subscription-Key": api_key}
    search_url = "https://api.bing.microsoft.com/v7.0/images/search"
    params = {"q": search_term, "count": num_images, "offset": 0, "imageType": "photo"}
    
    response = requests.get(search_url, headers=headers, params=params)
    response.raise_for_status()
    search_results = response.json()

    image_urls = [img["contentUrl"] for img in search_results["value"]]
    return image_urls

# Main function to crawl and download images
def crawl_images_bing(search_term, api_key, num_images=10):
    # Fetch image URLs using Bing Image Search API
    image_urls = bing_image_search(search_term, api_key, num_images)

    if len(image_urls) == 0:
        print("No images found!")
        return
    
    # Create folder to save images
    folder_name = search_term.replace(' ', '_')
    create_folder(folder_name)
    
    # Download the images
    for idx, img_url in enumerate(image_urls):
        image_name = f"{search_term.replace(' ', '_')}_{idx + 1}.jpg"
        download_image(img_url, folder_name, image_name)

if __name__ == "__main__":
    search_query = input("Enter the search term for images: ")
    number_of_images = int(input("Enter the number of images you want to download: "))
    
    # Enter your Bing API Key here
    BING_API_KEY = "your_bing_api_key_here"
    
    crawl_images_bing(search_query, BING_API_KEY, num_images=number_of_images)
