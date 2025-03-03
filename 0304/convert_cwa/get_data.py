import requests
import json
from datetime import datetime, timedelta

url = 'https://opendata.cwa.gov.tw/api/v1/rest/datastore/F-D0047-045'
params = {
    'Authorization': '******',
    'limit': 2,
    'format': 'JSON',
    'ElementName': '溫度',
    'sort': 'time'
}
headers = {
    'accept': 'application/json'
}

response = requests.get(url, headers=headers, params=params)

if response.status_code == 200:
    data = response.json()
    with open('/Users/fychao/Work/IoT-RD/0304/convert_cwa/data.json', 'w', encoding='utf-8') as f:
        parsed_data = []
        for location in data['records']['Locations']:
            for loc in location['Location']:
                location_name = loc['LocationName']
                for weather_element in loc['WeatherElement']:
                    for t_time in weather_element['Time']:
                        utc_time = datetime.strptime(t_time['DataTime'], '%Y-%m-%dT%H:%M:%S%z')
                        tpe_time = utc_time + timedelta(hours=8)  # Convert UTC to TPE (UTC+8)
                        parsed_data.append({
                            'location': location_name,
                            'tpe_time': tpe_time.strftime('%Y-%m-%d %H:%M:%S'),
                            'temperature': t_time['ElementValue'][0]['Temperature']
                        })
        json.dump(parsed_data, f, ensure_ascii=False, indent=4)
else:
    print(f"Failed to retrieve data: {response.status_code}")