from flask import Flask
from twilio.rest import TwilioRestClient
from token import auth_token, account_sid

app = Flask(__name__)

@app.route('/<path:url>', methods=['get'])
def home(url):
    client = TwilioRestClient(account_sid, auth_token)

    client.messages.create(body=url,
        to="+18565582697",
        from_="+18564578834")
    return "only got " + url

if __name__ == '__main__':
    app.run()

