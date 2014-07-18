from flask import Flask, request
from twilio.rest import TwilioRestClient
from twilio_info import auth_token, account_sid

app = Flask(__name__)
app.debug = True

@app.route('/<path:url>', methods=['get'])
def home(url):
    if request.method == 'GET':
        client = TwilioRestClient(account_sid, auth_token)
        message = client.messages.create(body="yo dawg",
                to="+18565582697",
                from_="+18564578834")
        return "request received"
if __name__ == '__main__':
    app.run()

