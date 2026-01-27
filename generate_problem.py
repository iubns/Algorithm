import sys
import os
import re

# Check for required packages
try:
    import requests
    from bs4 import BeautifulSoup
except ImportError:
    print("\n[!] Error: Missing required libraries.")
    print("Please install them by running:\n")
    print("    pip install requests beautifulsoup4")
    print("\nExiting...")
    sys.exit(1)

def clean_text(element):
    """
    Extract text, preserving some structure for blockquotes.
    """
    if not element:
        return ""
    
    # Process text
    # We want to preserve newlines from <br> and paragraph breaks
    for br in element.find_all("br"):
        br.replace_with("\n")
    
    # Get text
    text = element.get_text(separator="\n", strip=True)
    return text

def format_for_markdown(text):
    """
    Prefix every line with '> ' for blockquotes.
    """
    if not text:
        return "> None"
    
    lines = text.split('\n')
    # Remove empty lines at start/end
    cleaned_lines = []
    for line in lines:
        cleaned_lines.append(f"> {line}")
    
    return "\n".join(cleaned_lines)

def create_main_cpp(path):
    content = """#include <iostream>
#include <vector>
#include <algorithm>
#include <string>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    return 0;
}
"""
    with open(path, 'w', encoding='utf-8') as f:
        f.write(content)

def get_problem_info(problem_id):
    url = f"https://www.acmicpc.net/problem/{problem_id}"
    headers = {
        'User-Agent': 'Mozilla/5.0 (Macintosh; Intel Mac OS X 10_15_7) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/120.0.0.0 Safari/537.36'
    }
    
    try:
        response = requests.get(url, headers=headers)
        response.raise_for_status()
    except requests.exceptions.RequestException as e:
        print(f"[!] Request failed: {e}")
        return None

    soup = BeautifulSoup(response.text, 'html.parser')
    
    title_elem = soup.select_one('#problem_title')
    desc_elem = soup.select_one('#problem_description')
    input_elem = soup.select_one('#problem_input')
    output_elem = soup.select_one('#problem_output')
    
    info = {
        'id': problem_id,
        'title': title_elem.text.strip() if title_elem else "?",
        'desc': clean_text(desc_elem),
        'input': clean_text(input_elem),
        'output': clean_text(output_elem)
    }
    return info

def get_ordinal(n):
    if 10 <= n % 100 <= 20:
        suffix = 'th'
    else:
        suffix = {1: 'st', 2: 'nd', 3: 'rd'}.get(n % 10, 'th')
    
    if n == 1: return "once"
    if n == 2: return "twice"
    return f"{n}{suffix}"

def generate_readme(info, path, solved, tries, difficulty, etc):
    # Solve status
    if solved.lower() == 'y':
        solve_badge = "solve-success-brightgreen"
    else:
        solve_badge = "solve-fall-brightred"
        
    # Trial status
    try_text = get_ordinal(int(tries))
    trial_badge = f"trial-at%20{try_text}-green"
    
    # Difficulty status (mapping input number to text)
    diff_map = {
        '1': ("easy", "brightgreen"),
        '2': ("medium", "green"),
        '3': ("hard", "orange"),
        '4': ("very_hard", "red"),
        '5': ("hell", "darkred")
    }
    diff_text, diff_color = diff_map.get(str(difficulty), ("unknown", "gray"))
    diff_badge = f"difficulty-{diff_text}-{diff_color}"
    
    # ETC content
    etc_content = f"> {etc}" if etc.strip() else "> None"

    content = f"""[#{info['id']}. {info['title']}](https://www.acmicpc.net/problem/{info['id']})
![solve](https://img.shields.io/badge/{solve_badge})
![trial](https://img.shields.io/badge/{trial_badge})
![difficulty](https://img.shields.io/badge/{diff_badge})
---------------------------

## 문제 (Problem)
{format_for_markdown(info['desc'])}

## 입력 (Input)
{format_for_markdown(info['input'])}

## 출력 (Output)
{format_for_markdown(info['output'])}

## 기타 (ETC)
{etc_content}
"""
    with open(path, 'w', encoding='utf-8') as f:
        f.write(content)

def main():
    # Interactive Inputs
    problem_id = input("문제 번호를 입력하세요: ").strip()
    if not problem_id:
        print("[!] Problem ID is required.")
        sys.exit(1)

    solved_input = input("답지를 안보고 풀었나요? (y/n): ").strip().lower()
    tries_input = input("몇 번 만에 풀었나요? (숫자): ").strip()
    
    print("난이도는 어땠나요?")
    print("1: Easy, 2: Medium, 3: Hard, 4: Very Hard, 5: Hell")
    difficulty_input = input("난이도 (숫자 입력): ").strip()
    
    etc_input = input("기타 사항 (없으면 엔터): ").strip()

    base_folder = "BaekJoonCpp"
    target_folder = os.path.join(base_folder, problem_id)
    
    print(f"[*] Fetching problem {problem_id}...")
    info = get_problem_info(problem_id)
    if not info:
        print("[!] Could not fetch problem info.")
        sys.exit(1)
        
    print(f"[*] Found: {info['title']}")
    
    if not os.path.exists(target_folder):
        os.makedirs(target_folder)
        print(f"[*] Created directory: {target_folder}")
    else:
        print(f"[*] Directory already exists: {target_folder}")
        
    main_cpp_path = os.path.join(target_folder, "Main.cpp")
    if not os.path.exists(main_cpp_path):
        create_main_cpp(main_cpp_path)
        print(f"[*] Created Main.cpp")
    else:
        print(f"[!] Main.cpp already exists, skipping.")
        
    readme_path = os.path.join(target_folder, "README.md")
    generate_readme(info, readme_path, solved_input, tries_input, difficulty_input, etc_input)
    print(f"[*] Created/Updated README.md")
    
    print("\nDone!")

if __name__ == "__main__":
    main()
