from flask import Flask, request
from twilio.rest import TwilioRestClient
from twilio_info import auth_token, account_sid

app = Flask(__name__)
app.debug = True

@app.route('/<path:url>', methods=['get'])
def home(url):
    if request.method == 'GET' and url == 'ping':
        client = TwilioRestClient(account_sid, auth_token)
        message = client.messages.create(body="Honey Bunches of Oats supply depleted. Proceed with secondary breakfast protocol",
                to="+18565582697",
                from_="+18564578834")
    return "request recived"
if __name__ == '__main__':
    app.run()

