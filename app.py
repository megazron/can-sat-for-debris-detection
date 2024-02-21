import pickle, bz2
import numpy as np
import joblib
from flask import Flask, render_template, request
import os

app = Flask(__name__)


import pandas as pd
import nltk
from sklearn.preprocessing import StandardScaler
from nltk.corpus import stopwords
from nltk.stem import PorterStemmer, WordNetLemmatizer
from nltk.tokenize import word_tokenize
from collections import Counter
nltk.download('punkt')
nltk.download('wordnet')
nltk.download('stopwords')

# Load the pre-trained model
df = pd.read_csv('trimmed_data.csv')
#rf_pipeline_joblib = joblib.load('modeljob.pkl')
#rf_pipeline_joblib = pickle.load(open("modeljob.pkl", "rb"))

#Converting text to lowercase
df['clean_text'] = df['clean_text'].str.lower()
#Removing Numbers, Special Charecters, and Punctuations
df['clean_text'] = df['clean_text'].str.replace('[^a-zA-Z]', ' ')
#Tokenizing text into different words
df['tokens'] = df['clean_text'].apply(word_tokenize)

stemmer = PorterStemmer()
# Applying Stemming to each token
df['stemmed_tokens'] = df['tokens'].apply(lambda x: [stemmer.stem(token) for token in x])
lemmatizer = WordNetLemmatizer()
#Applying Lemmatization to all tokens
df['lemmatized_tokens'] = df['tokens'].apply(lambda x: [lemmatizer.lemmatize(token) for token in x])
# Retrieve the English stopwords
stop_words = set(stopwords.words('english'))
# Remove the stopwords from the dataset
df['clean_tokens'] = df['tokens'].apply(lambda x: [token for token in x if token not in stop_words])
# Remove the stopwords from the Lemmatized tokens
df['cleaned_tokens'] = df['lemmatized_tokens'].apply(lambda x: [token for token in x if token not in stop_words])

# Combine all lemmatized tokens into a single string
all_tokens = ' '.join(df['tokens'].sum())
# Combine all lemmatized tokens into a single string
all_tokens = ' '.join(df['stemmed_tokens'].sum())
# Combine all lemmatized tokens into a single string
all_tokens = ' '.join(df['cleaned_tokens'].sum())

# Filter rows where "is_depression" is 1
depression_data = df[df['is_debris'] == 1]
# Combine lemmatized tokens
combined_tokens = [token for tokens_list in depression_data['lemmatized_tokens'] for token in tokens_list]
# Combine lemmatized tokens into sentences
df['lemmatized_sentences'] = df['lemmatized_tokens'].apply(lambda tokens: ' '.join(tokens))

from sklearn.model_selection import train_test_split
from sklearn.feature_extraction.text import TfidfVectorizer
from sklearn.pipeline import Pipeline
from sklearn.linear_model import LogisticRegression
from sklearn.ensemble import RandomForestClassifier
from sklearn.svm import SVC
from sklearn.metrics import classification_report

X = df['lemmatized_sentences']  # Input data (lemmatized sentences)
y = df['is_debris']  # Target labels (0 or 1)
X_train, X_test, y_train, y_test = train_test_split(X, y, test_size=0.2, random_state=42)

# Create a pipeline with only Random Forest
rf_pipeline = Pipeline([
    ('tfidf', TfidfVectorizer()),
    ('classifier', RandomForestClassifier())
])
# Train the model
rf_pipeline.fit(X_train, y_train)
y_pred = rf_pipeline.predict(X_test)
report = classification_report(y_test, y_pred)
print(f"Classification Report:\n{report}\n")


# IMAGE_FOLDER = os.path.join('static', 'images')
# app.config['UPLOAD_FOLDER'] = IMAGE_FOLDER

@app.route('/')
def index():
    return render_template('index.html')

@app.route('/predict', methods=['POST'])
def predict():
    text_input = request.form['newsInput']
    prediction = rf_pipeline.predict([text_input])
    #prediction = rf_pipeline_joblib.predict([text_input])
    return render_template('index.html', result=prediction)

@app.route('/get_data')
def get_data():
    data_dict = df.to_dict(orient='records')
    return jsonify(data_dict)

# @app.route('/index')
# def show_index():
#     full_filename = os.path.join(app.config['UPLOAD_FOLDER'], 'loneliness.png')
#     return render_template("index.html", html_src_image = full_filename)

if __name__ == "__main__":
    app.run(debug=True, port=3004)


#http://127.0.0.1:3004