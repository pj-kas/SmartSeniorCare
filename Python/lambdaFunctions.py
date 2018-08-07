#Python Code for Lambda functions

##################snsVibration#########################################

import boto3

def lambda_handler(event, context):
    client = boto3.client('sns')
    response = client.publish(
            TargetArn="arn:aws:sns:us-east-1:011261327301:noMotion",
            Message="A fall has been detected!."
        )

#######################################################################



##################snsNoMotion#########################################

import boto3

def lambda_handler(event, context):
    client = boto3.client('sns')
    response = client.publish(
            TargetArn="arn:aws:sns:us-east-1:011261327301:noMotion",
            Message="No motion has been detected for 12 hours."
        )

#######################################################################
